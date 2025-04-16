import os
import numpy as np
with open('./7.in', 'r') as f:
    budget, n, k = map(int, f.readline().split())

    # Read the data
    data = f.readline().split()

    for i in range(n):
        data[i] = int(data[i])
    
    data = np.array(data)
    
    
    
    data = np.array(data)

    for i in range(n-223):
        if(np.unique(data[i:i+224]).size > k):
            print(i)
            break
    