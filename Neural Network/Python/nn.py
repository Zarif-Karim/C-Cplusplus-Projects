# import sys
# import numpy as np
# import matplotlib as mpl

# print("Python: ", sys.version)
# print("Numpy: ", np.__version__)
# print("Matplotlib: ", mpl.__version__)


inputs = [1.2,5.1,2.1]
weights = [3.1,2.1,8.7]

bias = 3

output = 0

for i in range(len(inputs)):
    output += inputs[i] * weights[i]
output += bias;

print(output)
