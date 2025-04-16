import os
import random

def generate_random_file_content():
    content = "P: {}\n".format(random.randint(1, 100))
    num_lines = random.randint(1, 10)
    for i in range(num_lines):
        content += "{}: {}\n".format(i, random.randint(1, 100))
    content += "N: {}\n".format(random.randint(1, 100))
    return content

def generate_files(directory, num_files):
    if not os.path.exists(directory):
        os.makedirs(directory)
    
    for i in range(num_files):
        filename = os.path.join(directory, f"file_0_{i}.txt")
        with open(filename, 'w') as f:
            f.write(generate_random_file_content())

if __name__ == "__main__":
    directory = "/Users/kodmas/Desktop/113CP/file_op/hw/2/"
    num_files = 5  # Change this to the number of files you want to generate
    generate_files(directory, num_files)