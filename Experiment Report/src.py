# data generating

import random
import numpy as np
import time

def ranStr(num, index):
    f = open('data' + str(index+1) + '.csv', 'w')
    s = 'abcdefghijklmnopqrstuvwxyz'

    for i in num:
        result = ''
        for j in range(0, i):
            result += random.choice(s)

        rank = np.random.randint(1, 65537)  # rank range
        f.writelines([result, ',', str(rank), '\n'])


# execute
echo = 5  # number of data set
num = np.random.randint(1, 17, size=1000000)  # length of words is between 1~17
sum = 0

for i in range(0, echo):
    start = time.time()
    ranStr(num, i)
    end = time.time()
    sum += (end-start)

print('Average time: ', sum/echo, 's')

