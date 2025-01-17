import os

import matplotlib.pyplot as plt

# Data points
x_coords = []
y_coords = []

with open('coordinates.txt', 'r') as file:
    lines = file.readlines()
    x_coords_line = lines[0].strip().replace('x_coords = [', '').replace(']', '')
    y_coords_line = lines[1].strip().replace('y_coords = [', '').replace(']', '')
    landing_coords_line = lines[2].strip().replace('Landing Location: (', '').replace(')', '')
    x_coords = [float(x) for x in x_coords_line.split(',') if x]
    y_coords = [float(y) for y in y_coords_line.split(',') if y]
    landing_coords = [float(coord) for coord in landing_coords_line.split(',') if coord]

# Plot the points with a lower gap between points
plt.figure(figsize=(8, 8))
plt.scatter(x_coords, y_coords, color='blue', label='Data Points', s=10)  # s is the marker size
plt.plot(x_coords, y_coords, color='red', linestyle='-', linewidth=1)  # linewidth is the line width

# Adding labels and title
plt.title("Graph of Coordinates", fontsize=14)
plt.xlabel("X Coordinate", fontsize=12)
plt.ylabel("Y Coordinate", fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()

# Set equal scaling for both axes
plt.gca().set_aspect('equal', adjustable='box')

# Mark the landing location
plt.scatter(landing_coords[0], landing_coords[1], color='green', label='Landing Location', s=50)

plt.show()

# Delete the coordinates file
os.remove('coordinates.txt')
