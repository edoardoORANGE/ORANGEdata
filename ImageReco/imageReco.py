import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
import os


#im = Image.open('a_image.tif')
#im.show()
j = 0
for i in range(20):
	filename = './test/im'+str(i+1)+'.png'
	im = Image.open(filename)	
        imarray = np.array(im)
        #print(imarray)
        y,x,_ = plt.hist(imarray.flatten())
        if(y[len(y)-1] > 10000):
                os.rename(filename , './tracks/im'+str(i+1)+'.png')
                j = j+1
print(j)

                
        
