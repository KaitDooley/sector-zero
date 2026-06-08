## What the Sigma? (Reverse Engineering)
When did Gen Alpha start developing programming languages?

# Steps:
1. Reading `message.txt`, we see a number of `sigma rules` followed by `yapping` statements. 
Reading `output.txt`, we see a list of words that are also seen in `message.txt`. 
Based on this and the rules looking like ascii values for characters, we will try to decode the output based on the corresponding rules

2. Write a simple script to process the sigma rules 
```
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
```

# Solution:
SVIBGR{G3n3r47i0n_4lph4_Is_C00k3d}
