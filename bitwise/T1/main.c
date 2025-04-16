#include <stdio.h>
#include <stdint.h>

uint32_t swap_blocks(uint32_t num, int k) {
    int block_size = 32 / k;
    uint32_t result = 0;
    
    for (int i = 0; i < k; i += 2) {
        uint32_t block1 = (num >> (i * block_size)) & ((1 << block_size) - 1);
        uint32_t block2 = 0;
        
        if (i + 1 < k) {
            block2 = (num >> ((i + 1) * block_size)) & ((1 << block_size) - 1);
        }
        
        result |= block1 << ((i + 1) * block_size);
        result |= block2 << (i * block_size);
    }
    
    return result;
}

int main() {
    uint32_t num = 3061544883;
    int k = 6;
    uint32_t swapped = swap_blocks(num, k);
    printf("%u\n", swapped);
    return 0;
}
