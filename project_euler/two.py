#!/usr/bin/env python3

import sys

MAX = 4000000

total = 0
n1 = 0
n2 = 1
curr = 0
for i in range(1, MAX + 1):
    n1 = n2
    n2 = curr
    curr = n1 + n2
    if curr > MAX:
        break
    if curr % 2 == 0:
        total += curr 
    
print(total)
