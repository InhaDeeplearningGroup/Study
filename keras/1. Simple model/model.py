__author__ = "kdhht5022@gmail.com"
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import keras
from keras.layers import TimeDistributed
from keras.layers import Dense, Activation, ZeroPadding2D, Dropout, Flatten
from keras.layers import GlobalMaxPooling2D
from keras.models import Sequential
from keras.layers.core import Dense, Dropout, Flatten
from keras.layers.convolutional import Conv2D, MaxPooling2D, ZeroPadding2D
from keras.optimizers import SGD, Adam
from keras import backend as K
from keras.engine import Input, Model
from keras.utils import np_utils
from keras.layers.normalization import BatchNormalization
from keras.preprocessing.image import ImageDataGenerator
from keras import regularizers

import numpy as np
np.random.seed(2 ** 10)

import logging
logging.basicConfig(level=logging.DEBUG)

import sys
sys.stdout = sys.stderr
sys.setrecursionlimit(2 ** 20)

x_shape = [64, 64, 3]
x_shape_flatten = [12288]


def DNN():
    model = Sequential()
    
    model.add(Dense(1024, input_shape=x_shape_flatten))
    model.add(Activation('relu'))
    model.add(Dropout(0.5))
    model.add(Dense(1024))
    model.add(Activation('relu'))
    model.add(Dropout(0.5))
    model.add(Dense(256))
    model.add(Activation('relu'))
    model.add(Dropout(0.5))
    model.add(Dense(2))
    model.add(Activation('linear'))
    model.summary()
    return model


def Simple_CNN():
    model = Sequential()
    
    model.add(Conv2D(16, (3, 3), padding='same', activation='relu', input_shape=x_shape))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    
    model.add(Conv2D(32, (3, 3), padding='same', activation='relu'))
    model.add(Conv2D(32, (3, 3), padding='same', activation='relu'))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    
    model.add(Conv2D(64, (3, 3), padding='same', activation='relu'))
    model.add(Conv2D(64, (3, 3), padding='same', activation='relu'))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    
    model.add(Conv2D(128, (3, 3), padding='same', activation='relu'))
    model.add(Conv2D(128, (3, 3), padding='same', activation='relu'))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    model.add(Flatten())
    
    model.add(Dense(512))
    model.add(Activation('relu'))
    model.add(Dropout(0.5))
    model.add(Dense(256))
    model.add(Activation('relu'))
    model.add(Dropout(0.5))
    model.add(Dense(2))
    model.add(Activation('linear'))
    model.summary()
    return model


