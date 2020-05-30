from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np
import pandas as pd
from numpy import genfromtxt

# df      = np.matrix(genfromtxt('h.csv', delimiter=','))

# Z = df[ 1800:2200 , 1800:2200 ]

# Z[Z < 0.3] = 0.3

# print(df.shape)

# Z = np.array(Z)
# _min = 0.3
# _max = Z.max()
# print(Z.shape)

X = np.arange(-6,6,1)
Y = np.arange(-6,6,1)

def f(x,y):
    return x**2+y**2

Z = f(X, Y)

ax = plt.axes(projection='3d')
ax.plot_surface(X, Y, Z, rstride=1, cstride=1,
                cmap='viridis', edgecolor='none');


fig = plt.figure()
ax = fig.gca(projection='3d')
 
X, Y = np.meshgrid(X, Y)

z = np.zeros((len(X),len(X)))

for x in range(len(X)):
    for y in range(len(Y)):
        z[x][y] = (f(x,y))

surf = ax.plot_surface(X, Y, z, cmap='viridis',linewidth=0, antialiased=False)
#
# Customize the z axis.
ax.set_zlim(_min, _max)

# set z ticks and labels
ax.xaxis.set_ticks(np.arange(0, 400, 100))
ax.yaxis.set_ticks(np.arange(0, 400, 100))
ax.set_zticks(np.arange(0.3,1.1,0.1))


ax.zaxis.set_major_formatter(FormatStrFormatter('%.1f'))
ax.set_xlabel('$x [pixels]$', fontsize=10)
ax.set_ylabel('$y [pixels]$', fontsize=10)
ax.set_zlabel('$height [m]$', fontsize=10)
# Add a color bar which maps values to colors.
cbar = fig.colorbar(surf, shrink=0.5, aspect=5)

cbar.ax.set_ylabel('Height [m]')

plt.savefig("height.svg", format="svg")
plt.show()

