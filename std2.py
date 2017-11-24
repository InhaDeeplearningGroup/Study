import argparse
import sys
import tempfile

from tensorflow.examples.tutorials.mnist import input_data

import tensorflow as tf
import numpy as np
import os
FLAGS = None


def deepnn(x):
    with tf.name_scope('block0'):
        with tf.name_scope('conv0'):
            W_conv = weight_variable([3, 3, 3, 16])
            b_conv = bias_variable([16])
            h_conv = tf.nn.relu(conv2d(x, W_conv) + b_conv)
        with tf.name_scope('conv1'):                              
            W_conv = weight_variable([3, 3, 16, 16])
            b_conv = bias_variable([16])
            h_conv = tf.nn.relu(conv2d(h_conv, W_conv) + b_conv)

        h_pool = max_pool_2x2(h_conv)
        
    with tf.name_scope('block1'):
        with tf.name_scope('conv0'):
            W_conv = weight_variable([3, 3, 16, 32])
            b_conv = bias_variable([32])
            h_conv = tf.nn.relu(conv2d(h_pool, W_conv) + b_conv)
        with tf.name_scope('conv1'):                              
            W_conv = weight_variable([3, 3, 32, 32])
            b_conv = bias_variable([32])
            h_conv = tf.nn.relu(conv2d(h_conv, W_conv) + b_conv)

        h_pool = max_pool_2x2(h_conv)
    with tf.name_scope('block2'):
        with tf.name_scope('conv0'):
            W_conv = weight_variable([3, 3, 32, 64])
            b_conv = bias_variable([64])
            h_conv = tf.nn.relu(conv2d(h_pool, W_conv) + b_conv)
        with tf.name_scope('conv1'):                              
            W_conv = weight_variable([3, 3, 64, 64])
            b_conv = bias_variable([64])
            h_conv = tf.nn.relu(conv2d(h_conv, W_conv) + b_conv)

        h_pool = max_pool_2x2(h_conv)
        
  # Fully connected layer 1 -- after 2 round of downsampling, our 28x28 image
  # is down to 7x7x64 feature maps -- maps this to 1024 features.
    with tf.name_scope('fc1'):
        W_fc1 = weight_variable([4 * 4 * 64, 256])
        b_fc1 = bias_variable([256])

        h_pool2_flat = tf.reshape(h_pool, [-1, 4*4*64])        
        h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)  

  # Dropout - controls the complexity of the model, prevents co-adaptation of
  # features.
    with tf.name_scope('dropout'):
        keep_prob = tf.placeholder(tf.float32)
        h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)

  # Map the 1024 features to 10 classes, one for each digit
    with tf.name_scope('fc2'):
        W_fc2 = weight_variable([256, 10])
        b_fc2 = bias_variable([10])

        y_conv = tf.matmul(h_fc1_drop, W_fc2) + b_fc2
    return y_conv, keep_prob


def conv2d(x, W):
    """conv2d returns a 2d convolution layer with full stride."""
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')


def max_pool_2x2(x):
    """max_pool_2x2 downsamples a feature map by 2X."""
    return tf.nn.max_pool(x, ksize=[1, 2, 2, 1],
                        strides=[1, 2, 2, 1], padding='SAME')


def weight_variable(shape):
    """weight_variable generates a weight variable of a given shape."""
    initial = tf.truncated_normal(shape, stddev=0.1)                  
    return tf.Variable(initial)                                      
                                                                     

def bias_variable(shape):
    """bias_variable generates a bias variable of a given shape."""
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)



slim = tf.contrib.slim

_SPLITS_TO_SIZES = {'train': 50000, 'test': 10000}

def get_dataset(split_name, dataset_dir, batch_size):
    file_pattern = os.path.join(dataset_dir, 'cifar10_%s.tfrecord' % split_name)
    
    reader = tf.TFRecordReader

    keys_to_features = {'image/encoded': tf.FixedLenFeature((), tf.string, default_value=''),
                        'image/format': tf.FixedLenFeature((), tf.string, default_value='png'),
                        'image/class/label': tf.FixedLenFeature([], tf.int64, default_value=tf.zeros([], dtype=tf.int64)),}
    items_to_handlers = {'image': slim.tfexample_decoder.Image(shape=[32, 32, 3]),
                         'label': slim.tfexample_decoder.Tensor('image/class/label')}

    decoder = slim.tfexample_decoder.TFExampleDecoder(keys_to_features, items_to_handlers)
    dataset =  slim.dataset.Dataset(data_sources=file_pattern,
                                    reader=reader,
                                    decoder=decoder,
                                    num_samples=_SPLITS_TO_SIZES[split_name],
                                    items_to_descriptions = None,
                                    num_classes=10)
    
    provider = slim.dataset_data_provider.DatasetDataProvider(dataset,
                                                              common_queue_capacity=20*batch_size,
                                                              common_queue_min=5*batch_size)
    images, labels = provider.get(['image', 'label'])    
    images = tf.to_float(images)
    
    
    
    batch_images, batch_labels = tf.train.shuffle_batch([images, labels],
                                                        batch_size = batch_size,
                                                        capacity = 20*batch_size, min_after_dequeue=5*batch_size)
    batch_labels = slim.one_hot_encoding(batch_labels, 10,on_value=1.0)
        
    batch_queue = slim.prefetch_queue.prefetch_queue([batch_images,batch_labels],
                                                      capacity = 20*batch_size)
    image, label = batch_queue.dequeue()
    
    return image, label

def main(_):
    # Import data
    print (FLAGS.data_dir)
    global_step = tf.train.create_global_step()
    
    train_x, train_y_ = get_dataset('train', FLAGS.data_dir, 128)
    with tf.device('gpu:0'):
        y_conv, keep_prob = deepnn(train_x)            
                                                                    
    
    with tf.name_scope('loss'):                                     
        cross_entropy = tf.nn.softmax_cross_entropy_with_logits(labels=train_y_,
                                                            logits=y_conv)
    cross_entropy = tf.reduce_mean(cross_entropy)   

    with tf.name_scope('adam_optimizer'):
        train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy, global_step = global_step) 

    with tf.name_scope('accuracy'):
        correct_prediction = tf.equal(tf.argmax(y_conv, 1), tf.argmax(train_y_, 1)) 
        correct_prediction = tf.cast(correct_prediction, tf.float32)
    accuracy = tf.reduce_mean(correct_prediction)
  
    tf.summary.scalar('accuracy', accuracy)  
    merged = tf.summary.merge_all()     
    
    graph_location = tempfile.mkdtemp()   
    print('Saving graph to: %s' % graph_location)
    
    config = tf.ConfigProto()   
    config.gpu_options.allow_growth=True       
    
    
    if FLAGS.Fine_tune:
        variables_to_restore = tf.contrib.framework.get_variables_to_restore()
        checkpoint_path = tf.train.latest_checkpoint('%s'%FLAGS.data_dir)
        saver = tf.train.Saver(variables_to_restore)
    else:
        saver = tf.train.Saver()
    
    with tf.Session(config=config) as sess:
        coord = tf.train.Coordinator()
        tf.train.start_queue_runners(sess=sess, coord=coord)
        
        train_writer = tf.summary.FileWriter('%s'%FLAGS.data_dir,
                                             sess.graph)
        if FLAGS.Fine_tune:
            saver.restore(sess, checkpoint_path)
        else:
            sess.run(tf.global_variables_initializer())
            
        for i in range(20000):
            if i % 100 == 0:
                train_accuracy, log = sess.run([accuracy,merged],feed_dict={keep_prob: 1.0})
                print('step %d, training accuracy %g' % (i, train_accuracy))
                train_writer.add_summary(log, i)
            if i % (50000//128)==0:
                print('new_model_saved')
                saver.save(sess, '%s/model.ckpt'%FLAGS.data_dir)
            train_step.run(feed_dict={keep_prob: 0.5})
        coord.request_stop()
        
if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--data_dir', type=str,
                        default='/home/dmsl/Documents/test',help='Directory for storing input data')
    parser.add_argument('--Fine_tune',type=bool, default=False,help='')
    parser.add_argument('--is_test'  ,type=bool, default=False,help='')
    FLAGS, unparsed = parser.parse_known_args()
    
    tf.app.run(main, argv=[sys.argv[0]] + unparsed)