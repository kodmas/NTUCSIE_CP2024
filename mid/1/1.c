#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
 
#define BITS_PER_UINT64 64
 
// Function to turn on a bulb (set the bit to 1)
void turn_on(uint64_t *bitset, int index) {
    bitset[index / BITS_PER_UINT64] |= (1ULL << (index % BITS_PER_UINT64));
}
 
// Function to turn off a bulb (set the bit to 0)
void turn_off(uint64_t *bitset, int index) {
    bitset[index / BITS_PER_UINT64] &= ~(1ULL << (index % BITS_PER_UINT64));
}
 
// Function to check if a bulb is on (check if the bit is 1)
bool is_on(uint64_t *bitset, int index) {
    return bitset[index / BITS_PER_UINT64] & (1ULL << (index % BITS_PER_UINT64));
}
 
// Optimized function to check if there's a light on the left
bool check_left(uint64_t *bitset, int current, int N) {
    int chunk_index = current / BITS_PER_UINT64;
    int bit_index = current % BITS_PER_UINT64;

    // First, check bits to the left within the current chunk
    if (bit_index > 0) {
        uint64_t mask = (1ULL << bit_index) - 1;  // Mask for bits to the left of current bit
        if (bitset[chunk_index] & mask) {
            return true;  // There's a bit on to the left in this chunk
        }
    }

    // Then, check chunks to the left of the current chunk
    for (int i = chunk_index - 1; i >= 0; i--) {
        if (bitset[i] != 0) {
            return true;  // Early exit: there's a bit on in this chunk
        }
    }

    return false;
}

// Optimized function to check if there's a light on the right
bool check_right(uint64_t *bitset, int current, int N) {
    int chunk_index = current / BITS_PER_UINT64;
    int bit_index = current % BITS_PER_UINT64;

    // First, check bits to the right within the current chunk
    if (bit_index < BITS_PER_UINT64 - 1) {
        uint64_t mask = ~((1ULL << (bit_index + 1)) - 1);  // Mask for bits to the right of current bit
        if (bitset[chunk_index] & mask) {
            return true;  // Early exit: there's a bit on to the right in this chunk
        }
    }

    // Then, check chunks to the right of the current chunk
    for (int i = chunk_index + 1; i < (N + BITS_PER_UINT64 - 1) / BITS_PER_UINT64; i++) {
        if (bitset[i] != 0) {
            return true;  // Early exit: there's a bit on in this chunk
        }
    }

    return false;
}

 
int main() {
    int N, k, M;
 
    // Read the values of N, k, and M
    scanf("%d", &N);
 
    int *t = (int *)malloc(N * sizeof(int));  // time-lightbulb map
    for (int i = 0; i < N; i++) {
        scanf("%d", &t[i]);
    }
 
    scanf("%d", &k);
 
    scanf("%d", &M);
 
    // Dynamically allocate memory for bitset and time-lightbulb map (t) and queue
    int num_uint64 = (N + BITS_PER_UINT64 - 1) / BITS_PER_UINT64;  // Number of uint64_t needed to cover N bits
    uint64_t *bitset = (uint64_t *)calloc(num_uint64, sizeof(uint64_t));  // Bitset to represent lightbulb states
 
    int *queue = (int *)malloc(N * sizeof(int));  // array to maintain the order of the turned-on bulbs
    int front = 0, rear = 0;  // pointers for the queue
 
 
 
    int current = k;  // current index
    bool found = false;
 
    while (true) {
        // Turn on the current lightbulb
        turn_on(bitset, current);
 
        // Add the current bulb to the queue
        queue[rear++] = current;
 
        // Check if we need to turn off the oldest light
        if (rear - front > M) {
            int bulb_to_turn_off = queue[front++];
            turn_off(bitset, bulb_to_turn_off);
        }
 
        // Check if there's a light on to the left and to the right
        bool left_on = check_left(bitset, current, N);
        bool right_on = check_right(bitset, current, N);
 
        if (left_on && right_on) {
            printf("%d", current);
            found = true;
            break;
        }
 
        // Jump to the next lightbulb based on the map
        current = t[current];
    }
 
 
    // Free dynamically allocated memory
    free(bitset);
    free(t);
    free(queue);
 
    return 0;
}