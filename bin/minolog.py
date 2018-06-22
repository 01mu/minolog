import json
import time
import matplotlib.pyplot as plt
import numpy as np
from pprint import pprint

#  get graph type
with open('mingraph.txt') as f:
    first_line = f.readline()

type = first_line

yCor = []
xCor = []

# type: graph-pb
if type == "graph-pbs":
    with open('graph.txt') as data_file:
        data = json.load(data_file)

    length = len(data)

    for x in range(0, length):
        seconds = data[x]['seconds']

        yCor.insert(x, seconds)
        xCor.insert(x, x)

# type: graph-pern
if type == "graph-pern":
    with open('graph.txt') as data_file:
        data = json.load(data_file)

    length = len(data)

    for x in range(0, length):
        seconds = data[x]['seconds']

        yCor.insert(x, seconds)
        xCor.insert(x, x)

plt.plot(xCor, yCor, color = 'blue')
plt.show()

input()

# with open('json.txt') as data_file:
#     data = json.load(data_file)
# length = len(data)
#
# yCor = []
# xCor = []
#
# averages = []
# total = 0
# iter = 0
# lin = 0
# get data
# for x in range(0, length):
#     if data[x]['totalLines'] >= 40 and data[x]['minutes'] == 0:
#         iter = iter + 1
#         lin = lin + 1
#         total = total + data[x]['seconds']
#
#         if iter % 100 == 0:
#             yCor.insert(x, total / 100)
#             xCor.insert(x, lin)
#             total = 0
#             iter = 0
#
# plot
# plt.plot(xCor, yCor, color='blue')
# plt.show()
