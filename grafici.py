import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("dataset.txt")

plt.grid()
plt.scatter(data[:,0] , data[:,1])

#plt.errorbar(data[: ,0] , data[: , 1] , xerr = data[: , 2] , yerr = data[: , 3] , fmt = '*' , capsize = 5 , elinewidth = 1 , ecolor = 'r')

plt.show()




