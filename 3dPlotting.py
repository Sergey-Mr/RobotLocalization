import matplotlib
matplotlib.use("TkAgg")

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Close any existing plots
plt.close('all')

# Read data, skipping the header line
data = np.loadtxt("probability_data.txt", skiprows=1)

data_normalized = data / np.max(data)  

rows, cols = data.shape
x = np.arange(cols)  
y = np.arange(rows)  
x, y = np.meshgrid(x, y)  

fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')

surf = ax.plot_surface(x, y, data_normalized, cmap='viridis', edgecolor='k')

ax.set_xlabel('X-axis (Columns)')
ax.set_ylabel('Y-axis (Rows)')
ax.set_zlabel('Probability (Normalized)')
ax.set_title('3D Probability Distribution (Normalized)')
fig.colorbar(surf, ax=ax, shrink=0.5, aspect=10)

plt.show()