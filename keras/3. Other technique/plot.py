__author__ = "kdhht5022@gmail.com"
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import csv
import sys
import numpy as np
import matplotlib.pyplot as plt


def plot_result():    
    
    f = open('./../your/path/*.csv', 'rt')
    
    list = []
    try:
        reader = csv.reader(f)
        for row in reader:
            list.append(row)
    finally:
        f.close()
        
        
    x_list = []
    y_list = []
    for i in range(1, len(list)):
        x_list.append(list[i][0])
        y_list.append(list[i][1])
    x = np.asarray(x_list, dtype=np.float32)
    y = np.asarray(y_list, dtype=np.float32)
    
    epochs = np.arange(1, len(list), 1)
        
    plt.plot(epochs, x, 'r-', label='x_value')
    plt.plot(epochs, y, 'b-', label='y_value')
    plt.xlabel('#epochs')
    plt.ylabel('test error (%)')

    plt.legend(loc='upper right')
    plt.grid(True)
    plt.xlim(0.0, 300.0)
    plt.ylim(0.0, 10.0)
    plt.show()
    plt.clf()
    plt.close()


if __name__ == '__main__':
    plot_result()
