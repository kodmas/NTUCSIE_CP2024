#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to find the index of the closest bike to the person using binary search
int find_closest_bike(int *bikes, int bikeCount, int person) {
    int low = 0, high = bikeCount - 1;

    // Binary search to find the bike closest to 'person'
    while (low < high) {
        int mid = (low + high) / 2;
        if (bikes[mid] < person) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    // Now 'low' is the index of the smallest bike >= person
    // Check both low and low - 1, to find the closest bike
    if (low == 0) {
        // Person is to the left of all bikes, return the first bike
        return low;
    }
    if (low == bikeCount) {
        // Person is to the right of all bikes, return the last bike
        return bikeCount - 1;
    }
    
    // Compare the bikes at 'low' and 'low - 1'
    if (abs(bikes[low] - person) < abs(bikes[low - 1] - person)) {
        return low;
    } else {
        return low - 1;
    }
}

// Function to output the bikes sorted by distance to each person using two pointers
void sort_bikes_by_distance(int *bikes, int bikeCount, int *people, int peopleCount) {
    for (int i = 0; i < peopleCount; i++) {
        int person = people[i];
        
        // Find the closest bike using binary search
        int closest_idx = find_closest_bike(bikes, bikeCount, person);
        
        // printf("closest_idx: %d\n", closest_idx);
        // Use two pointers to expand outwards from the closest bike
        int left = closest_idx - 1;
        int right = closest_idx;
        
        // Output bikes in order of distance
        while (left >= 0 || right < bikeCount) {
            if (left < 0) {
                // No more bikes on the left, take from the right
                printf("%d ", bikes[right++]);
            } else if (right >= bikeCount) {
                // No more bikes on the right, take from the left
                printf("%d ", bikes[left--]);
            } else {
                // Compare bikes on the left and right, take the closer one
                if (abs(bikes[left] - person) <= abs(bikes[right] - person)) {
                    printf("%d ", bikes[left--]);
                } else {
                    printf("%d ", bikes[right++]);
                }
            }
        }
        printf("\n");
    }
}



int main() {
    // Example input
    int N;
    scanf("%d", &N);

    int *bikes = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &bikes[i]);
    }
    
    int M;
    scanf("%d", &M);

    int *people = (int *)malloc(M * sizeof(int));
    for (int i = 0; i < M; i++) {
        scanf("%d", &people[i]);
    }

    
    // Call the function to sort and display the bikes by distance
    sort_bikes_by_distance(bikes, N, people, M);
    
    return 0;
}
