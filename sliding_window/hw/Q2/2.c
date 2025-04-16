#include "stdio.h"
#include "stdlib.h"

int main(){
    int budget, N, k;
    scanf("%d %d %d", &budget, &N, &k);

    int *arr = (int*)malloc(N * sizeof(int));

    for(int i=0;i<N;i++){
        scanf("%d", &arr[i]);
    }

    // frequency array
    int *freq = (int*)calloc(100000, sizeof(int));
    
    int count = 0;
    int sum = 0;

    int left = 0;
    int right = k-1;
    int min_len = 0;
    
    for(int i=0;i<k;i++){
        if(freq[arr[i]] == 0){
            count++;
        }
        freq[arr[i]]++;
        sum += arr[i];
    }

    while(left <= N-k){
        if(sum < budget){
            right++;
            if(right == N){
                break;
            }
            if(freq[arr[right]] == 0){
                count++;
            }
            freq[arr[right]]++;
            sum += arr[right];
        }
        else if(right - left + 1 < k){
            right++;
            if(right == N){
                break;
            }
            if(freq[arr[right]] == 0){
                count++;
            }
            freq[arr[right]]++;
            sum += arr[right];
        }
        else{
            if(count >= k){
                if(min_len == 0){
                    min_len = right - left + 1;
                }
                else{
                    min_len = min_len < right - left + 1 ? min_len : right - left + 1;
                }
                freq[arr[left]]--;
                if(freq[arr[left]] == 0){
                    count--;
                }
                sum -= arr[left];
                left++;
            }
            else{
                right++;
                if(right == N){
                    break;
                }
                if(freq[arr[right]] == 0){
                    count++;
                }
                freq[arr[right]]++;
                sum += arr[right];
            }
            
        }
    }

    if(min_len == 0){
        printf("-1");
    }
    else{
        printf("%d", min_len);
    }

    
    
    

    

    


    
}