import numpy as np
import matplotlib.pyplot as plt

x = ["C++", "C#", "Python", "Java", "Go"]
y = [20, 50, 140, 1, 45]

plt.bar(x, y, color="green", width=0.5, edgecolor="yellow", lw=3)
plt.show()
