# Implementing the algorithm to solve the problem using the input data from the file

file_path = "./3.in"

# Read the input file
with open(file_path, "r") as file:
    lines = file.readlines()

# Parse the input
N = int(lines[0].strip())  # Number of elements in the array
arr = list(map(int, lines[1].split()))  # Array of integers

# Initialize answer
ans = 0

# Go through each bit position (up to 32 bits)
for i in range(32):
    count = 0
    for j in range(N):
        if arr[j] & (1 << i):
            count += 1
    # If count of 1s is more than half, set the bit in ans
    if count > N // 2:
        ans |= (1 << i)

# Calculate the total XOR summation with the found ans
total = 0
for i in range(N):
    total += arr[i] ^ ans

print(ans, total)  # Return the computed 'x' and the total XOR summation
