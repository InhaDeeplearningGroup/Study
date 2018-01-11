__author__ = "kdhht5022@gmail.com"
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import tensorflow as tf
from keras.backend.tensorflow_backend import set_session
config = tf.ConfigProto()
config.gpu_options.per_process_gpu_memory_fraction = 0.3
config.gpu_options.allow_growth = True
config.gpu_options.visible_device_list = "0"
set_session(tf.Session(config=config))


import keras

'''
        ...
        ...
        ....

'''