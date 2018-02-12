__author__ = "KimDaeHa"
# -*- coding: utf-8 -*-
# %%
import os
import cv2
import scipy as sp
import numpy as np
from six.moves import xrange
import matplotlib.pyplot as plt
import logging
logging.basicConfig(level=logging.DEBUG)

# %%

def load_from_npz(data_name):
    with sp.load(data_name) as f:
        values = [f['arr_%d' % i] for i in range(len(f.files))][0]
        return values


def main():
    x_train_name = '/../../ImageNet_32/x_train.npz'
    x_test_name = '/../../ImageNet_32/x_test.npz'
    y_train_name = '/../../ImageNet_32/y_train.npz'
    y_test_name = '/../../ImageNet_32/y_test.npz'
    x_train = load_from_npz(x_train_name)
    x_test = load_from_npz(x_test_name)
    y_train = load_from_npz(y_train_name)
    y_test = load_from_npz(y_test_name)
    #plt.imshow(x_test[0])
    y_train = np.reshape(y_train, len(y_train)).astype(np.int64)
    for i in xrange(len(y_test)):
        y_train[i] = y_train[i] - 1
        y_test[i] = y_test[i] - 1
        
    # save ImageNet test images to png format
    for i in xrange(len(y_test)):
        label = y_test[i]
        if not os.path.exists('/../../ImageNet_32/test/'+str(label)):
            os.makedirs('/../../ImageNet_32/test/'+str(label))
        cv2.imwrite('/../../ImageNet_32/test/'+str(label)+'/image_'+str(i)+'.png', x_test[i])
        
    
    # save ImageNet train images to png format
    for i in xrange(len(y_train)):
        label = y_train[i]
        if not os.path.exists('/../../ImageNet_32/train/'+str(label)):
            os.makedirs('/../../ImageNet_32/train/'+str(label))
        cv2.imwrite('/../../ImageNet_32/train/'+str(label)+'/image_'+str(i)+'.png', x_train[i])

if __name__ == "__main__":
    main()
    