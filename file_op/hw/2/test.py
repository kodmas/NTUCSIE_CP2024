import os

def compute_hash(data_entries, nonce):
    # Compute the hash as defined
    H = 0
    all_data = data_entries + [nonce]  # Include the nonce as the last entry
    for data in all_data:
        H = ((H << 5) | (H >> 27)) & 0xFFFFFFFF  # 32-bit logical left shift
        H = (H ^ int(data)) & 0xFFFFFFFF  # XOR and ensure 32-bit
    return H

def parse_block(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
    
    prev_hash = int(lines[0].split(":")[1].strip())  # Get previous hash
    data_entries = []
    for line in lines[1:]:
        if line.startswith("N:"):
            nonce = int(line.split(":")[1].strip())
        else:
            data_entries.append(int(line.split(":")[1].strip()))
    return prev_hash, data_entries, nonce

def validate_ledger(file_names):
    n = len(file_names)
    prev_hash = 0  # Initial previous hash is 0

    for i in range(n - 1):  # Ignore the last block as per the problem statement
        # Parse current block
        curr_prev_hash, data_entries, nonce = parse_block(file_names[i])
        
        # Verify previous hash
        if curr_prev_hash != prev_hash:
            return i + 1  # 1-based index
        
        # Compute current hash
        curr_hash = compute_hash(data_entries, nonce)
        
        # Parse next block's previous hash
        next_prev_hash, _, _ = parse_block(file_names[i + 1])
        
        # Validate hash chain
        if curr_hash != next_prev_hash:
            return i + 2  # 1-based index of faulty block
        
        prev_hash = curr_hash  # Update previous hash for the next iteration
    
    return -1  # If all blocks are valid

if __name__ == "__main__":
    # Input reading
    n = int(input())
    file_names = [input().strip() for _ in range(n)]
    
    # Validate ledger and print result
    result = validate_ledger(file_names)
    print(result)
