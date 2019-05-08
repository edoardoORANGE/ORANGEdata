from PIL import Image
import numpy as np
import matplotlib.pyplot as plt

from mpl_toolkits.mplot3d import Axes3D

im = Image.open('track1.png')
ima = np.array(im)

ima_lin = ima.flatten()


x = np.zeros(len(ima_lin)/4)
y = np.zeros(len(ima_lin)/4)
z = np.zeros(len(ima_lin)/4)

j = 0
n = 0
for i in ima_lin:
    if j == 0:
        j = j + 1
        x[n] = i

    elif j == 1:
        j = j + 1
        y[n] = i
        
    elif j == 2:
        j = j + 1
        z[n] = i
        n = n + 1

    elif j == 3:
        j = 0
    
