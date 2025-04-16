#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to find the index of the closest bike to the person using binary search
int find_closest_bike(double *dists, int bikeCount, int person) {
    int low = 0, high = bikeCount - 1;

    // Binary search to find the bike closest to 'person'
    while (low < high) {
        int mid = (low + high) / 2;
        if (dists[mid] < person) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    // Now 'low' is the index of the smallest bike >= person
    // Check both low and low - 1, to find the closest bike
    if (low == 0) {
        // Person is to the left of all dists, return the first bike
        return low;
    }
    if (low == bikeCount) {
        // Person is to the right of all dists, return the last bike
        return bikeCount - 1;
    }
    
    // Compare the dists at 'low' and 'low - 1'
    if (fabs(dists[low] - person) <= fabs(dists[low - 1] - person)) {
        return low;
    } else {
        return low - 1;
    }
}

int modify_closest_idx(double* dists, int bikes[][2],int closest_idx){
    // printf("closest_idx: %d\n", closest_idx);
    int new_idx = closest_idx;
    if(dists[closest_idx] > 0){
        while(dists[closest_idx] == dists[closest_idx-1]){
            closest_idx--;
        }
        // closest_idx++;
    }
    else{
        while(dists[closest_idx] == dists[closest_idx+1]){
            closest_idx++;
        }
        // closest_idx--;
    }
    // printf("closest_idx: %d\n", closest_idx);
    new_idx = closest_idx;
    return new_idx;
    
}

// Function to output the bikes sorted by distance to each person using two pointers
void sort_bikes_by_distance(double *dists, int bikeCount,int bikes[][2],double orig_dist) {
    
    // Find the closest bike using binary search
    int closest_idx = find_closest_bike(dists, bikeCount, 0);
    closest_idx = modify_closest_idx(dists,bikes,closest_idx);
    // printf("closest_idx: %d\n", closest_idx);
    // Use two pointers to expand outwards from the closest bike
    int left = closest_idx - 1;
    int right = closest_idx;
    
    // Output dists in order of distance
    while (left >= 0 || right < bikeCount) {
        // printf("left = %d, right = %d\n",left,right);
        if (left < 0) {
            // No more dists on the left, take from the right
            printf("(%d,%d)", bikes[right][0],bikes[right][1]);
            right++;
            // printf("%d ", dists[right++]);
        } else if (right >= bikeCount) {
            // No more dists on the right, take from the left
            printf("(%d,%d)", bikes[left][0],bikes[left][1]);
            left--;
            // printf("%d ", dists[left--]);
        } else {
            // printf("dists[left]: %f, dists[right]: %f\n",dists[left],dists[right]);
            // Compare dists on the left and right, take the closer one
            if (fabs(dists[left] - 0) < fabs(dists[right] - 0)) {
                printf("(%d,%d)", bikes[left][0],bikes[left][1]);
                left--;
                // printf("%d ", dists[left--]);
            } 
            else if(fabs(dists[left] - 0) == fabs(dists[right] - 0)){
                if(sqrt(pow(bikes[left][0],2)+pow(bikes[left][1],2)) < sqrt(pow(bikes[right][0],2)+pow(bikes[right][1],2))){
                    printf("(%d,%d)", bikes[left][0],bikes[left][1]);
                    left--;
                }
                else{
                    printf("(%d,%d)", bikes[right][0],bikes[right][1]);
                    right++;
                }
            }
            else {
                printf("(%d,%d)", bikes[right][0],bikes[right][1]);
                right++;
                // printf("%d ", dists[right++]);
            }
        }
    }
}



int main() {
    // Example input
    int N;
    scanf("%d", &N);

    int bikes[N][2];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &bikes[i][0],&bikes[i][1]);
    }
    
    int M;
    scanf("%d", &M);

    int people_x;
    int people_y;

    double* dist = (double*)malloc(sizeof(double)*N);
    
    double orig_dist = 0;

    for(int i=0;i<M;i++){
        scanf("%d %d",&people_x,&people_y);
        orig_dist = sqrt(pow(people_x,2)+pow(people_y,2));

        for(int j=0;j<N;j++){
            dist[j] = sqrt(pow(bikes[j][0],2)+pow(bikes[j][1],2)) - sqrt(pow(people_x,2)+pow(people_y,2));
        }

        // for(int j=0;j<N;j++){
        //     printf("%f ",dist[j]);
        // }
        // printf("\n");

        sort_bikes_by_distance(dist, N, bikes,orig_dist);
        printf("\n");
    }
    
    
    
    return 0;
}
