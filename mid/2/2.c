#include <stdio.h>
#include <stdlib.h>

// Comparator function for qsort
int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to calculate the total operations required to make all elements in the window equal to the median
long long calculateOperations(int arr[], int start, int end) {
    int median = arr[(start + end) / 2];  // Median of the current window
    long long operations = 0;
    
    // Calculate total operations to make all elements equal to the median
    for (int i = start; i <= end; i++) {
        operations += abs(arr[i] - median);
    }
    
    return operations;
}

int maxEqualElementsWithMedian(int arr[], int n, int k) {
    // Sort the array
    qsort(arr, n, sizeof(int), cmp);
    
    int maxCount = 1;  // At least one element can always be made the same
    int start = 0;
    
    // Sliding window
    for (int end = 1; end < n; end++) {
        // Calculate the cost to make all elements in the window [start, end] equal to the median
        long long operations = calculateOperations(arr, start, end);
        
        // If operations exceed k, reduce the window size by moving start
        while (operations > k && start < end) {
            start++;
            operations = calculateOperations(arr, start, end);  // Recalculate the operations for the new window
        }
        
        // Update the maximum number of elements that can be made the same
        maxCount = (end - start + 1) > maxCount ? (end - start + 1) : maxCount;
    }
    
    return maxCount;
}


int main() {
    
    int n, k;
    scanf("%d %d", &n, &k);

    int *arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int result = maxEqualElementsWithMedian(arr, n, k);

    printf("%d", result);
    
    return 0;
}
