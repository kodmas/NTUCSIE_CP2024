#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_N 2097152

// Macros to manipulate bits in a 64-bit integer array
#define SET_BIT(arr, idx) (arr[(idx) / 64] |= (1ULL << ((idx) % 64)))
#define CLEAR_BIT(arr, idx) (arr[(idx) / 64] &= ~(1ULL << ((idx) % 64)))
#define GET_BIT(arr, idx) ((arr[(idx) / 64] >> ((idx) % 64)) & 1)

// Function to check if any bit is set between 0 and end_idx (exclusive)
int any_bulb_on_left(int64_t bulbs[], int end_idx) {
    int word_idx = end_idx / 64;
    int bit_offset = end_idx % 64;

    // Check if any bits are on in words before word_idx
    for (int i = 0; i < word_idx; i++) {
        if (bulbs[i] != 0) {
            return 1;  // There is at least one bulb on to the left
        }
    }

    // Check bits within the word at word_idx (left part of end_idx)
    if ((bulbs[word_idx] & ((1ULL << bit_offset) - 1)) != 0) {
        return 1;
    }

    return 0;
}

// Function to check if any bit is set between start_idx and N-1
int any_bulb_on_right(int64_t bulbs[], int start_idx, int N) {
    int word_idx = start_idx / 64;
    int bit_offset = start_idx % 64;

    // Check bits within the word at word_idx (right part of start_idx)
    if ((bulbs[word_idx] & (~((1ULL << bit_offset) - 1))) != 0) {
        return 1;
    }

    // Check if any bits are on in words after word_idx
    for (int i = word_idx + 1; i < (N + 63) / 64; i++) {
        if (bulbs[i] != 0) {
            return 1;  // There is at least one bulb on to the right
        }
    }

    return 0;
}

// Main function to solve the problem
int solve(int N, int k, int M, int t[]) {
    int64_t bulbs[(MAX_N + 63) / 64] = {0};  // Bitset to track bulb states
    int queue[M];  // Circular queue to store the last M lightbulbs
    int front = 0, rear = 0, count_on = 0;

    // Start at index k
    int i = k;

    // Turn on the first bulb
    SET_BIT(bulbs, i);
    queue[rear++] = i;  // Enqueue the index of the bulb
    count_on++;

    while (1) {
        // Move to the next index using the t array
        i = t[i];

        // Turn on the next bulb
        SET_BIT(bulbs, i);
        queue[rear++] = i;  // Enqueue the index
        if (rear == M) rear = 0; // Circular queue handling
        count_on++;

        // If there are more than M bulbs on, turn off the earliest one
        if (count_on > M) {
            int earliest = queue[front++];  // Dequeue the earliest bulb
            if (front == M) front = 0;  // Circular queue handling
            CLEAR_BIT(bulbs, earliest);  // Turn off the bulb
            count_on--;
        }

        // Check if there are bulbs on both left and right of the current bulb
        if (any_bulb_on_left(bulbs, i) && any_bulb_on_right(bulbs, i, N)) {
            return i;  // Stop and return the current index
        }
    }

    return -1;  // Shouldn't happen, but just in case
}

int main() {
    int N, k, M;

    // Read the values of N, k, and M
    scanf("%d", &N);

    int* t = (int*)malloc(N * sizeof(int));  // time-lightbulb map

    for (int i = 0; i < N; i++) {
        scanf("%d", &t[i]);
    }

    scanf("%d", &k);

    scanf("%d", &M);

    // Solve the problem
    int result = solve(N, k, M, t);

    // Output the result
    printf("Stopped at index: %d\n", result);

    return 0;
}
