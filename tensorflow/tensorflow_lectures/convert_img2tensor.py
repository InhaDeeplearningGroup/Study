import tensorflow as tf
import sys
import numpy as np
import pickle
from six.moves import xrange
LABELS_FILENAME = 'labels.txt'

##
def int64_feature(values):
    if not isinstance(values, (tuple, list)):
        values = [values]
    return tf.train.Feature(int64_list=tf.train.Int64List(value=values))

def bytes_feature(values):
    return tf.train.Feature(bytes_list=tf.train.BytesList(value=[values]))
  
def image_to_tfexample(image_data, image_format, class_id):
    return tf.train.Example(features=tf.train.Features(feature={'image/encoded': bytes_feature(image_data),
                                                                'image/format ': bytes_feature(image_format),
                                                                'image/class/label': int64_feature(class_id)}))
  
### main
convert_dir = '/home/dmsl/Documents/test'
dataset_dir = '/home/dmsl/Documents/data/cifar10'


dataset_type = 'png'

training_filename = '%s/cifar10_train.tfrecord' % (convert_dir)
test_filename     = '%s/cifar10_test.tfrecord'  % (convert_dir)

with tf.device('/cpu:0'):
    with tf.Session() as sess:
        image_placeholder = tf.placeholder(dtype=tf.uint8)
        encoded_image = tf.image.encode_png(image_placeholder)
        dataset_len = 0
        with tf.python_io.TFRecordWriter(training_filename) as tfrecord_writer:
            for batch in range(1,6):
                with open('%s/data_batch_%d'%(dataset_dir, batch), 'rb') as fo:
                    img_queue = pickle.load(fo, encoding='bytes')
                
                for n in xrange(img_queue[b'data'].shape[0]):
                    image = img_queue[b'data'][n]
                    image = np.transpose(image.reshape(3,32,32),(1,2,0))
                    label = img_queue[b'labels'][n]
                    image_string = sess.run(encoded_image,
                                      feed_dict={image_placeholder: image})
                    example = image_to_tfexample(image_string, str.encode(dataset_type), int(label))
                    tfrecord_writer.write(example.SerializeToString())
                    sys.stdout.write('\r>> Reading train_dataset images %d/%d' 
                                     % (n+dataset_len+1 , 5*img_queue[b'data'].shape[0]))
                dataset_len += img_queue[b'data'].shape[0]
        sys.stdout.write('\r\n') 
        with tf.python_io.TFRecordWriter(test_filename) as tfrecord_writer:
            with open('%s/test_batch'%dataset_dir, 'rb') as fo:
                img_queue = pickle.load(fo, encoding='bytes')
            
            for n in xrange(img_queue[b'data'].shape[0]):
                image = img_queue[b'data'][n]
                image = np.transpose(image.reshape(3,32,32),(1,2,0))
                label = img_queue[b'labels'][n]
                image_string = sess.run(encoded_image,
                                  feed_dict={image_placeholder: image})
                example = image_to_tfexample(image_string, str.encode(dataset_type), int(label))
                tfrecord_writer.write(example.SerializeToString())
                sys.stdout.write('\r>> Reading test_dataset images %d/%d' 
                                 % (n+1 , img_queue[b'data'].shape[0]))
                    
