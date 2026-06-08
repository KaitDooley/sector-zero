#!/usr/bin/env python3
import re

# Parse sigma rules from message.txt
word_to_char = {}
with open("message.txt") as f:
    for line in f:
        m = re.search(r'sigma rule (\d+):\s*yapping\("(\w+)"\)', line)
        if m:
            word_to_char[m.group(2)] = chr(int(m.group(1)))

# Decode output.txt
with open("output.txt") as f:
    words = [line.strip() for line in f if line.strip()]

print("".join(word_to_char.get(w, f"?({w})") for w in words))
