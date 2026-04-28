#!/usr/bin/env python3

import sys

MAX = 300000

total = 0
for i in range(1, MAX + 1):
    squared = pow(i, 2)
    if squared % 2 == 1:
        total += squared

print(total)
