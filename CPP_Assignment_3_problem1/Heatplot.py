import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate

filename = 'field.txt'

field_grid = np.loadtxt(filename)

rows, cols = field_grid.shape

x = np.arange(cols)  # Column indices
y = np.arange(rows)  # Row indices

interpolator = interpolate.RegularGridInterpolator((y, x), field_grid, method='linear')

# Create a finer grid for interpolation (twice the resolution)
x_new = np.linspace(0, cols - 1, 2 * cols)  # Finer x grid (columns)
y_new = np.linspace(0, rows - 1, 2 * rows)  # Finer y grid (rows)

# Create a meshgrid for the new finer grid (this will give us x_new, y_new pairs)
X_new, Y_new = np.meshgrid(x_new, y_new)

# Interpolate the data on the finer grid using RegularGridInterpolator
field_grid_interpolated = interpolator((Y_new, X_new)) 

plt.imshow(field_grid_interpolated, cmap='plasma', origin='lower', interpolation='nearest')

plt.colorbar()

plt.title("Interpolated Heatmap of Field Matrix from File")
plt.xlabel("Column Index")
plt.ylabel("Row Index")

output_filename = 'Poisson’s_Heatmap.png'  
plt.savefig(output_filename, dpi=300, bbox_inches='tight')  # Save with high resolution

plt.show()  

plt.close()