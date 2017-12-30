import time

import numpy
import tensorflow as tf
from tensorflow import ConfigProto

import model

FLAGS = tf.app.flags.FLAGS

tf.app.flags.DEFINE_string('device', '/gpu:0', "device")

tf.app.flags.DEFINE_string('dataset', 'cifar10', "{cifar10, svhn}")

tf.app.flags.DEFINE_string('log_dir', "", "log_dir")
tf.app.flags.DEFINE_integer('seed', 1, "initial random seed")

tf.app.flags.DEFINE_integer('batch_size', 32, "the number of examples in a batch")
tf.app.flags.DEFINE_integer('eval_batch_size', 100, "the number of eval examples in a batch")
tf.app.flags.DEFINE_integer('eval_freq', 5, "")
tf.app.flags.DEFINE_integer('num_epochs', 300, "the number of epochs for training")
tf.app.flags.DEFINE_integer('epoch_decay_start', 250, "epoch of starting learning rate decay")
tf.app.flags.DEFINE_integer('num_iter_per_epoch', 400, "the number of updates per epoch")
tf.app.flags.DEFINE_float('learning_rate', 0.001, "initial leanring rate")
tf.app.flags.DEFINE_integer('num_eval_examples', 5000, "number of evaluation examples")
tf.app.flags.DEFINE_float('mom1', 0.9, "initial momentum rate")
tf.app.flags.DEFINE_float('mom2', 0.5, "momentum rate after epoch_decay_start")


if FLAGS.dataset == 'cifar10':
    from cifar10_full import inputs
elif FLAGS.dataset == 'svhn':
    from svhn_full import inputs
else: 
    raise NotImplementedError


def ce_loss(logit, y):
    return tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=logit, labels=y))


def accuracy(logit, y):
    pred = tf.argmax(logit, 1)
    true = tf.argmax(y, 1)
    return tf.reduce_mean(tf.to_float(tf.equal(pred, true)))


def build_training_graph(x, y, lr, mom):
    global_step = tf.get_variable(name="global_step", shape=[], dtype=tf.float32,
                                  initializer=tf.constant_initializer(0.0), trainable=False)
    logit = model.cnn(x, is_training=True, update_batch_stats=True, stochastic=True, seed=FLAGS.seed)
    loss = ce_loss(logit, y)

    opt = tf.train.AdamOptimizer(learning_rate=lr, beta1=mom)
    tvars = tf.trainable_variables()
    grads_and_vars = opt.compute_gradients(loss, tvars)
    train_op = opt.apply_gradients(grads_and_vars, global_step=global_step)
    return loss, train_op, global_step


def build_eval_graph(x, y):
    losses = {}
    logit = model.cnn(x, is_training=False, update_batch_stats=False, stochastic=True, seed=FLAGS.seed)
    loss = ce_loss(logit, y)
    losses['loss'] = loss
    acc = accuracy(logit, y)
    losses['accuracy'] = acc
    return losses


def main(_):
    numpy.random.seed(seed=FLAGS.seed)
    tf.set_random_seed(numpy.random.randint(1234))
    
    with tf.Graph().as_default() as g:
        with tf.device("/cpu:0"):
            images, labels = inputs(batch_size=FLAGS.batch_size, train=True, shuffle=True)
            images_test, labels_test = inputs(batch_size=FLAGS.eval_batch_size, train=False, shuffle=True)

        with tf.device(FLAGS.device):
            lr = tf.placeholder(tf.float32, shape=[], name="learning_rate")
            mom = tf.placeholder(tf.float32, shape=[], name="momentum")
            with tf.variable_scope("CNN") as scope:
                loss, train_op, global_step = build_training_graph(images, labels, lr, mom)
                scope.reuse_variables()  # essential!
                
                losses_eval_test = build_eval_graph(images_test, labels_test)

            init_op = tf.global_variables_initializer()

        if not FLAGS.log_dir:
            logdir = None
            writer_train = None
            writer_test = None
        else:
            logdir = FLAGS.log_dir
            writer_train = tf.summary.FileWriter(FLAGS.log_dir + "/train", g)
            writer_test = tf.summary.FileWriter(FLAGS.log_dir + "/test", g)

        saver = tf.train.Saver(tf.global_variables())
        sv = tf.train.Supervisor(is_chief=True, logdir=logdir, init_op=init_op,
                                 init_feed_dict={lr: FLAGS.learning_rate, mom: FLAGS.mom1},
                                 saver=saver, global_step=global_step, summary_op=None, summary_writer=None,
                                 save_model_secs=150, recovery_wait_secs=0)

        print("Training start!!")
        config = ConfigProto()
        config.gpu_options.allow_growth=True  # to handle GPU memory
        with sv.managed_session(config=config) as sess:
            for ep in range(FLAGS.num_epochs):
                if sv.should_stop():
                    break

                if ep < FLAGS.epoch_decay_start:
                    feed_dict = {lr: FLAGS.learning_rate, mom: FLAGS.mom1}
                else:
                    decayed_lr = ((FLAGS.num_epochs - ep) / float(
                        FLAGS.num_epochs - FLAGS.epoch_decay_start)) * FLAGS.learning_rate
                    feed_dict = {lr: decayed_lr, mom: FLAGS.mom2}

                sum_loss = 0
                start = time.time()
                for i in range(FLAGS.num_iter_per_epoch):
                    batch_loss, _, _ = sess.run([loss, train_op, global_step],
                                                feed_dict=feed_dict)
                    sum_loss += batch_loss
                end = time.time()
                print("[INFO] Epoch:", ep, "Train_loss:", sum_loss / FLAGS.num_iter_per_epoch, "Per_epoch_time:", end - start)

                if (ep + 1) % FLAGS.eval_freq == 0 or ep + 1 == FLAGS.num_epochs:
                    act_values_dict = {}
                    for key, _ in losses_eval_test.iteritems():
                        act_values_dict[key] = 0
                    n_iter_per_epoch = FLAGS.num_eval_examples / FLAGS.eval_batch_size
                    for i in range(n_iter_per_epoch):
                        values = losses_eval_test.values()
                        act_values = sess.run(values)
                        for key, value in zip(act_values_dict.keys(), act_values):
                            act_values_dict[key] += value
                    summary = tf.Summary()
                    current_global_step = sess.run(global_step)
                    for key, value in act_values_dict.iteritems():
                        print("test " + key, value / n_iter_per_epoch)
                        summary.value.add(tag=key, simple_value=value / n_iter_per_epoch)
                    if writer_test is not None:
                        writer_test.add_summary(summary, current_global_step)

            saver.save(sess, sv.save_path, global_step=global_step)
        sv.stop()


if __name__ == "__main__":
    tf.app.run()
