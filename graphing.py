from mpl_toolkits import mplot3d

import numpy as np
import matplotlib.pyplot as plt
import csv

X = []
Y = []
Z = []

with open('Output.txt', 'r') as datafile:
    ploting = csv.reader(datafile, delimiter=',')
      
    for ROWS in ploting:
        X.append(float(ROWS[0]))
        Y.append(float(ROWS[1]))
        Z.append(float(ROWS[2]))

fig = plt.figure()
ax = plt.axes(projection="3d")

# z_line = np.linspace(0, 15, 1000)
# x_line = np.cos(z_line)
# y_line = np.sin(z_line)
ax.plot3D(X, Y, Z, 'green')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
plt.show()

