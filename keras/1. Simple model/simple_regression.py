__author__ = "kdhht5022@gmail.com"
#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import numpy as np
np.random.seed(2 ** 10)

import scipy as sp
from math import sqrt
from six.moves import xrange

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

import logging
logging.basicConfig(level=logging.DEBUG)

import sys
sys.stdout = sys.stderr
sys.setrecursionlimit(2 ** 20)

from model import DNN, Simple_CNN

num_classes = 2
batch_size = 8
data_augmentation = True
maxepoches = 250
learning_rate = 0.001
lr_decay = 1e-6
lrf = learning_rate
weight_decay = 0.0005


def normalize(X_train,X_test):
    mean = np.mean(X_train,axis=(0,1,2,3))
    std = np.std(X_train, axis=(0,1,2,3))
    X_train = (X_train-mean)/(std+1e-7)
    X_test = (X_test-mean)/(std+1e-7)
    return X_train, X_test


def load_from_npz(data_name):
    with sp.load(data_name) as f:
        values = [f['arr_%d' % i] for i in range(len(f.files))][0]
        return values
    
    
def root_mean_squared_error(y_true, y_pred):
        return K.sqrt(K.mean(K.square(y_pred - y_true), axis=-1)) 
    
    
X_data_name_1 = '../../.npz'
y_data_name_1 = '../../.npz'
X_data_name_2 = '../../.npz'
y_data_name_2 = '../../.npz'
X_train, y_train = load_from_npz(X_data_name_1), load_from_npz(y_data_name_1)
X_test, y_test = load_from_npz(X_data_name_2), load_from_npz(y_data_name_2)

X_train, X_test = normalize(X_train, X_test)

# %% DNN (only fully-connected layer)

dnn = DNN()

X_train = np.reshape(X_train, (len(X_train), len(X_train[1])*len(X_train[2])*3))
X_test = np.reshape(X_test, (len(X_test), len(X_train[1])*len(X_train[2])*3))

#optimization details
adam = Adam(lr=lrf, decay=lr_decay)
dnn.compile(loss='mse', optimizer=adam, metrics=[RMSE_aousal, RMSE_valence])

for epoch in range(1, maxepoches):

    if epoch % 25 == 0 and epoch > 0:
        lrf /= 2
        adam = Adam(lr=lrf, decay=lr_decay)
        dnn.compile(loss='mse', optimizer=adam, metrics=[RMSE_aousal, RMSE_valence])
        
    dnn.fit(X_train, y_train, epochs=epoch, initial_epoch=epoch-1, 
            shuffle=True, batch_size=batch_size,
            validation_data=(X_test, y_test), callbacks=[])
    

# %% Deep CNN (VGG like)
    
simple_cnn = Simple_CNN()

X_train = np.reshape(X_train, (len(X_train), len(X_train[1]), len(X_train[2]), 3))
X_test = np.reshape(X_test, (len(X_test), len(X_train[1]), len(X_train[2]), 3))

#optimization details
adam = Adam(lr=lrf, decay=lr_decay)
simple_cnn.compile(loss='mse', optimizer=adam, metrics=[RMSE_aousal, RMSE_valence])

if not data_augmentation:
    simple_cnn.fit(X_train, y_train, epochs=maxepoches, shuffle=True, batch_size=batch_size,
                   validation_data=(X_test, y_test), callbacks=[])
    
else:
    #data augmentation
    datagen = ImageDataGenerator(
        rotation_range=15,  # randomly rotate images in the range (degrees, 0 to 180)
        width_shift_range=0.125,  # randomly shift images horizontally (fraction of total width)
        height_shift_range=0.125,  # randomly shift images vertically (fraction of total height)
        horizontal_flip=True)  # randomly flip images
    # (std, mean, and principal components if ZCA whitening is applied).
    datagen.fit(X_train)
    
    
    # training process in a for loop with learning rate drop every 25 epoches.
    
    for epoch in range(1,maxepoches):
    
        if epoch % 25 == 0 and epoch > 0:
            lrf /= 2
            adam = Adam(lr=lrf, decay=lr_decay)
            simple_cnn.compile(loss='mse', optimizer=adam, metrics=[RMSE_aousal, RMSE_valence])
    
        historytemp = simple_cnn.fit_generator(datagen.flow(X_train, y_train, batch_size=batch_size),
                                               steps_per_epoch=X_train.shape[0] // batch_size,
                                               epochs=epoch, initial_epoch=epoch-1, 
                                               validation_data=(X_test, y_test), callbacks=[])
    
