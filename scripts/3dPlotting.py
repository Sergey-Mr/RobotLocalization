import matplotlib
matplotlib.use("TkAgg")

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.interpolate import griddata

# Close existing plots
plt.close('all')

# Read data
data = np.loadtxt("probability_data.txt", skiprows=1)
data_normalized = data / np.max(data)  

# Create original grid points
rows, cols = data.shape
x_orig = np.arange(cols)
y_orig = np.arange(rows)
x_grid_orig, y_grid_orig = np.meshgrid(x_orig, y_orig)

# Create finer grid with more interpolation points
x_fine = np.linspace(0, cols-1, cols*10)  # Increased interpolation
y_fine = np.linspace(0, rows-1, rows*10)
x_grid_fine, y_grid_fine = np.meshgrid(x_fine, y_fine)

# Interpolate data with cubic method
points = np.column_stack((x_grid_orig.flatten(), y_grid_orig.flatten()))
values = data_normalized.flatten()
z_grid_fine = griddata(points, values, (x_grid_fine, y_grid_fine), method='cubic')

# Create figure and position window
fig = plt.figure(figsize=(10, 7))
manager = plt.get_current_fig_manager()
manager.window.geometry("+1200+0")  # Position right of main window

# Create 3D plot with enhanced visuals
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(x_grid_fine, y_grid_fine, z_grid_fine, 
                      cmap='viridis',
                      antialiased=True,
                      linewidth=0,
                      rcount=200,        
                      ccount=200,
                      alpha=0.9)         

# Adjust view angle for better visualization
ax.view_init(elev=30, azim=45)

# Customize axes
ax.set_xlabel('X-axis (Columns)')
ax.set_ylabel('Y-axis (Rows)')
ax.set_zlabel('Probability (Normalized)')
ax.set_title('3D Probability Distribution')

# Add colorbar with custom size
fig.colorbar(surf, ax=ax, shrink=0.5, aspect=10, pad=0.1)

# Show plot
plt.show()