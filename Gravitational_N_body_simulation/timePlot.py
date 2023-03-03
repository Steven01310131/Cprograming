import matplotlib as plt
import matplotlib.pyplot as plt
import numpy as np

f1 = open('pth3000.txt', 'r')
f2 = open('pth5000.txt', 'r')
f3 = open('pth10000.txt', 'r')

x1 = []
x2 = []
x3 = []


for line in f1:
    x1.append(float(line))

for line in f2:
    x2.append(float(line))

for line in f3:
    x3.append(float(line))

plt.plot(x1, label='3000')
plt.plot(x2, label='5000')
plt.plot(x3, label='10000')
plt.legend()
plt.ylabel('Time (s)')
plt.xlabel('Number of Threads')
plt.show()
