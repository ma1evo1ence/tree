import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('SET.txt')

dataA = np.loadtxt('AVL.txt')

x = []
y_insert = []
y_find = []
y_delete = []

xA = []
y_insertA = []
y_findA = []
y_deleteA = []

for i in range(len(data)):
    x.append(data[i][0])
    y_insert.append(data[i][1])
    y_find.append(data[i][2])
    y_delete.append(data[i][3])

for i in range(len(dataA)):
    xA.append(dataA[i][0])
    y_insertA.append(dataA[i][1])
    y_findA.append(dataA[i][2])
    y_deleteA.append(dataA[i][3])

insert, =  plt.plot(x, y_insert)
insert.set_label('Insert')
insertA, =  plt.plot(x, y_insertA)
insertA.set_label('Insert AVL')
find, = plt.plot(x, y_find)
find.set_label('Find')
findA, = plt.plot(xA, y_findA)
findA.set_label('FindA')
delete, = plt.plot(x, y_delete)
delete.set_label('Delete')
deleteA, = plt.plot(xA, y_deleteA)
deleteA.set_label('DeleteA')
plt.legend(loc='upper left')
plt.show()
