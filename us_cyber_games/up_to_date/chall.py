import random
import string

def chall():
    random.seed(42)
    zenc_code = """REDACTED"""

    # Split the Zen-C code into five chunks
    num_strides = 5
    chunks = [zenc_code[i::num_strides] for i in range(num_strides)]

    packets = []
    # Valid packets: [Magic: ZN (2 bytes)][Seq (1 byte)][Len (1 byte)][Payload (Len bytes)]
    for seq_id, text in enumerate(chunks):
        # Secure the payload by starting it with its sequence ID
        payload_str = str(seq_id) + text
        payload = payload_str.encode('utf-8')
        header = b'ZN' + bytes([seq_id, len(payload)])
        packets.append(header + payload)

    def random_payload(length):
        return "".join(random.choices(string.ascii_letters + string.digits, k=length)).encode('utf-8')

    # Noisy packet 1: Wrong magic bytes
    for _ in range(10):
        bad_magic = bytes(random.choices(range(256), k=2))
        if bad_magic == b'ZN':
            bad_magic = b'XX'
        rand_len = random.randint(5, 25)
        packets.append(bad_magic + bytes([random.randint(0, 255), rand_len]) + random_payload(rand_len))

    # Noisy packet 2: Wrong payload start (not matching with sequence ID)
    for _ in range(10):
        dup_seq = random.randint(0, num_strides - 1)
        rand_len = random.randint(5, 25)
        
        bad_payload = random_payload(rand_len)
        # Make sure the bad payload doesn't start with correct sequence ID
        if bad_payload.startswith(str(dup_seq).encode('utf-8')):
            bad_payload = b'X' + bad_payload[1:]
            
        packets.append(b'ZN' + bytes([dup_seq, len(bad_payload)]) + bad_payload)

    random.shuffle(packets)
    full_stream = b"".join(packets)
    hex_output = full_stream.hex()

    with open("output.txt", "w") as f:
        f.write(hex_output)

if __name__ == "__main__":
    chall()
