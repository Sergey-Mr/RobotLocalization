import matplotlib
matplotlib.use("TkAgg")

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.interpolate import griddata

# Close any existing plots
plt.close('all')

# Read data, skipping the header line
data = np.loadtxt("probability_data.txt", skiprows=1)

# Normalize data
data_normalized = data / np.max(data)  

# Create original grid points
rows, cols = data.shape
x_orig = np.arange(cols)
y_orig = np.arange(rows)
x_grid_orig, y_grid_orig = np.meshgrid(x_orig, y_orig)

# Create finer grid for interpolation
x_fine = np.linspace(0, cols-1, cols*5)
y_fine = np.linspace(0, rows-1, rows*5)
x_grid_fine, y_grid_fine = np.meshgrid(x_fine, y_fine)

# Interpolate data
points = np.column_stack((x_grid_orig.flatten(), y_grid_orig.flatten()))
values = data_normalized.flatten()
z_grid_fine = griddata(points, values, (x_grid_fine, y_grid_fine), method='cubic')

# Create plot
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')

# Plot surface with smoother parameters
surf = ax.plot_surface(x_grid_fine, y_grid_fine, z_grid_fine, 
                      cmap='viridis',
                      antialiased=True,
                      linewidth=0,
                      rcount=100,
                      ccount=100)

ax.set_xlabel('X-axis (Columns)')
ax.set_ylabel('Y-axis (Rows)')
ax.set_zlabel('Probability (Normalized)')
ax.set_title('3D Probability Distribution (Normalized)')
fig.colorbar(surf, ax=ax, shrink=0.5, aspect=10)

plt.show()