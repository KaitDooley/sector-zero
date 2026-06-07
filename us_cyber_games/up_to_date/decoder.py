#!/usr/bin/env python3

import re

# Read the hex file and convert it to raw bytes
raw = bytes.fromhex(open("output.txt").read().strip())

# We expect 5 chunks (the encoder split the message into 5 interleaved slices)
NUM_CHUNKS = 5

# This dict will hold the recovered text for each chunk, keyed by sequence ID (0-4)
chunks = {}

i = 0
while i < len(raw):

    # Every valid packet starts with the 2-byte magic "ZN"
    # If we don't see it, this isn't a valid packet start — skip one byte and try again
    if raw[i:i+2] != b'ZN':
        i += 1
        continue

    # Parse the 4-byte header:
    #   bytes 0-1 : magic "ZN"  (already confirmed above)
    #   byte  2   : sequence ID (which chunk this belongs to, 0-4)
    #   byte  3   : payload length in bytes
    seq_id  = raw[i+2]
    length  = raw[i+3]

    # Extract the payload (everything after the 4-byte header)
    payload = raw[i+4 : i+4+length]

    # Advance i to the start of the next packet
    i += 4 + length

    # The encoder secured each payload by prepending the sequence ID as an ASCII digit
    # e.g. chunk 3's payload starts with b'3...'
    # If it doesn't, this is a noise packet — discard it
    if payload[:1] != str(seq_id).encode():
        continue

    # Strip that leading sequence-ID byte to get the actual chunk text
    # Only keep the first valid packet per sequence ID (duplicates are noise)
    if seq_id not in chunks:
        chunks[seq_id] = payload[1:].decode('utf-8')

# Reassemble the original message.
# The encoder interleaved characters with a stride of 5:
#   original[0], original[5], original[10], ... → chunk 0
#   original[1], original[6], original[11], ... → chunk 1
#   etc.
# So to reverse it, we interleave the chunks back together:
max_len = max(len(chunks[s]) for s in range(NUM_CHUNKS))
result = []
for pos in range(max_len):           # for each character position within a chunk
    for stride in range(NUM_CHUNKS): # interleave across all 5 chunks
        if pos < len(chunks[stride]):
            result.append(chunks[stride][pos])

zenc_code = "".join(result)

# Parse the Zen-C code: extract the array of hex values and the XOR key
code = [int(x, 16) for x in re.findall(r'0x[0-9a-f]+', zenc_code.split('let key')[0])]
key  = int(re.search(r'let key = (0x[0-9a-f]+)', zenc_code).group(1), 16)

# Execute the Zen-C logic: XOR each byte with the key to get the flag
flag = "".join(chr(b ^ key) for b in code)
print(flag)
