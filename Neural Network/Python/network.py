import random

import numpy as np

class Network(object):

    def __init__(self, sizes) -> None:
        self.num_layers = len(sizes);
        self.sizes = sizes;
        self.biases = [np.random.randn(y, 1) for y in sizes[1:]];



data = [[5,4,2,1,6,9,7,8,11,23,48],[5,4,2,1,6,9,7,8,11,23,48]] ;
network = [5,4,2];

#z = [np.random.randn(y,x) for x,y in zip(sizes[:-1],sizes[1:])]

#print(z);

#print([data[z:z+5] for z in range(0,len(data),5)])
data = np.array(data)
print(data.shape)
