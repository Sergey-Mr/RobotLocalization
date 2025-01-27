import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Step 1: Read the data from the file
file_name = "probability_distribution.txt"
data = np.loadtxt(file_name)

# Step 2: Normalize the data for better visualization
data_normalized = data / np.max(data)  # Scale values to range [0, 1]

# Step 3: Create a grid for plotting
rows, cols = data.shape
x = np.arange(cols)  # Column indices
y = np.arange(rows)  # Row indices
x, y = np.meshgrid(x, y)  # Create a grid

# Step 4: Create a 3D plot
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')

# Plot the surface
surf = ax.plot_surface(x, y, data_normalized, cmap='viridis', edgecolor='k')

# Add labels and a color bar
ax.set_xlabel('X-axis (Columns)')
ax.set_ylabel('Y-axis (Rows)')
ax.set_zlabel('Probability (Normalized)')
ax.set_title('3D Probability Distribution (Normalized)')
fig.colorbar(surf, ax=ax, shrink=0.5, aspect=10)

# Show the plot
plt.show()
