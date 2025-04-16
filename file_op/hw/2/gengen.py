import random

# Function to generate a single file with valid data
def generate_file(filename, start_index, line_count, prev_result):
    with open(filename, "w") as f:
        # Write P value
        f.write(f"P: {prev_result}\n")
        
        # Write data values
        result = 0
        for i in range(1, line_count + 1):
            value = random.randint(1, 100)
            f.write(f"{i}: {value}\n")
            
            # XOR calculation with special rules for multiples of 25
            if i % 25 == 0:
                result ^= value
                result = (result << 1) % (1 << 30)
            else:
                result ^= value
                result %= (1 << 30)
        
        # Write the N value
        f.write(f"N: {result}\n")
        
        return result

# Generate three files with over 50 lines of data
line_count = 55  # Number of data lines in each file
prev_result = random.randint(1, 100)  # Initial result for the first file
file_names = ["test_block_1_1.txt", "test_block_1_2.txt", "test_block_1_3.txt"]

for i, file_name in enumerate(file_names):
    prev_result = generate_file(file_name, i + 1, line_count, prev_result)

file_names
