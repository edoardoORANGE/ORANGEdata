import numpy as np
import matplotlib.pyplot as plt
from PIL import Image


filename = 'track3.png'
im = Image.open(filename)
ima = np.array(im)

plt.hist(ima.flatten() , bins = 50)
plt.show()
