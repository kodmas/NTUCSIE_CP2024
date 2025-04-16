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
int check_left(uint64_t *bitset, int current, int last_left_found) {
    if (last_left_found != -1 && last_left_found < current) {
        return last_left_found; // Last found left is still valid
    }

    int chunk_index = current / BITS_PER_UINT64;
    int bit_index = current % BITS_PER_UINT64;

    // Check bits to the left within the current chunk
    if (bit_index > 0) {
        uint64_t mask = (1ULL << bit_index) - 1; // Mask for bits to the left of current bit
        if (bitset[chunk_index] & mask) {
            for (int i = bit_index - 1; i >= 0; i--) {
                if (bitset[chunk_index] & (1ULL << i)) {
                    return chunk_index * BITS_PER_UINT64 + i;
                }
            }
        }
    }

    // Check chunks to the left of the current chunk
    for (int i = chunk_index - 1; i >= 0; i--) {
        if (bitset[i] != 0) {
            for (int j = BITS_PER_UINT64 - 1; j >= 0; j--) {
                if (bitset[i] & (1ULL << j)) {
                    return i * BITS_PER_UINT64 + j;
                }
            }
        }
    }

    return -1;
}

// Optimized function to check if there's a light on the right
int check_right(uint64_t *bitset, int current, int N, int last_right_found) {
    if (last_right_found != -1 && last_right_found > current) {
        return last_right_found; // Last found right is still valid
    }

    int chunk_index = current / BITS_PER_UINT64;
    int bit_index = current % BITS_PER_UINT64;

    // Check bits to the right within the current chunk
    if (bit_index < BITS_PER_UINT64 - 1) {
        uint64_t mask = ~((1ULL << (bit_index + 1)) - 1); // Mask for bits to the right of current bit
        if (bitset[chunk_index] & mask) {
            for (int i = bit_index + 1; i < BITS_PER_UINT64; i++) {
                if (bitset[chunk_index] & (1ULL << i)) {
                    return chunk_index * BITS_PER_UINT64 + i;
                }
            }
        }
    }

    // Check chunks to the right of the current chunk
    for (int i = chunk_index + 1; i < (N + BITS_PER_UINT64 - 1) / BITS_PER_UINT64; i++) {
        if (bitset[i] != 0) {
            for (int j = 0; j < BITS_PER_UINT64; j++) {
                if (bitset[i] & (1ULL << j)) {
                    return i * BITS_PER_UINT64 + j;
                }
            }
        }
    }

    return -1;
}

int main() {
    int N, k, M;

    // Read the values of N, k, and M
    // printf("Enter number of lightbulbs (N): ");
    scanf("%d", &N);

    int *t = (int *)malloc(N * sizeof(int));  // time-lightbulb map
    // printf("Enter time-lightbulb map (N values): ");
    for (int i = 0; i < N; i++) {
        scanf("%d", &t[i]);
    }

    // printf("Enter start index (k): ");
    scanf("%d", &k);

    // printf("Enter maximum simultaneous lights on (M): ");
    scanf("%d", &M);

    // Dynamically allocate memory for bitset and time-lightbulb map (t) and queue
    int num_uint64 = (N + BITS_PER_UINT64 - 1) / BITS_PER_UINT64;  // Number of uint64_t needed to cover N bits
    uint64_t *bitset = (uint64_t *)calloc(num_uint64, sizeof(uint64_t));  // Bitset to represent lightbulb states
    
    int *queue = (int *)malloc(N * sizeof(int));  // array to maintain the order of the turned-on bulbs
    int front = 0, rear = 0;  // pointers for the queue

    int current = k;  // current index
    bool found = false;

    int last_left_found = -1;   // Last known index with light on to the left
    int last_right_found = -1;  // Last known index with light on to the right
    int previous_index = -1;    // Track the previous index

    while (true) {
        printf("%d ",current);
        // Turn on the current lightbulb
        turn_on(bitset, current);

        // Add the current bulb to the queue
        queue[rear++] = current;

        // Check if we need to turn off the oldest light
        if (rear - front > M) {
            int bulb_to_turn_off = queue[front++];
            turn_off(bitset, bulb_to_turn_off);

            // Update last_left_found/right_found if it affects the edges
            if (bulb_to_turn_off == last_left_found) {
                last_left_found = -1;  // Invalidate the left found if it was turned off
            }
            if (bulb_to_turn_off == last_right_found) {
                last_right_found = -1;  // Invalidate the right found if it was turned off
            }
        }

        // Check the relationship between previous index and current index
        if (previous_index != -1) {
            if (current > previous_index && last_left_found == -1) {
                // Current is to the right of the previous index and no left bulb is found
                // Skip checking left
                last_left_found = -1;
            } else if (current < previous_index && last_right_found == -1) {
                // Current is to the left of the previous index and no right bulb is found
                // Skip checking right
                last_right_found = -1;
            } else {
                // Check for lightbulbs only if necessary
                last_left_found = check_left(bitset, current, last_left_found);
                last_right_found = check_right(bitset, current, N, last_right_found);
            }
        } else {
            // No previous index to compare, so check both sides
            last_left_found = check_left(bitset, current, last_left_found);
            last_right_found = check_right(bitset, current, N, last_right_found);
        }

        // If both left and right are found, we can stop
        if (last_left_found != -1 && last_right_found != -1) {
            printf("%d", current);
            found = true;
            break;
        }

        // Jump to the next lightbulb based on the map
        previous_index = current; // Update previous index
        current = t[current];
    }

    // Free dynamically allocated memory
    free(bitset);
    free(t);
    free(queue);

    return 0;
}
