#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(){
    int M,N;

    scanf("%d %d", &M, &N);

    char* str = (char*)malloc(sizeof(char)*N);

    scanf("%s", str);

    int left = 0;

    while(left < N){
        if(str[left] == 'A' || str[left] == 'C' || str[left] == 'G' || str[left] == 'T'){
            left++;
        }
        else{
            break;
        }   
    }

    while(left < N){
        if(str[left] != 'A' && str[left] != 'C' && str[left] != 'G' && str[left] != 'T'){
            left++;
        }
        else{
            break;
        }
    }


    char* palin = (char*)malloc(sizeof(char)*(M/2));

    int temp = left;
    int i = 0;
    while(temp < N && i < M/2){
        if(str[temp] == 'A' || str[temp] == 'C' || str[temp] == 'G' || str[temp] == 'T'){
            palin[i] = str[temp];
            i++;
            temp++;
        }
        else{
            temp++;
        }
    }

    if(left == N){
        for(int i=0;i<M/2;i++){
            palin[i] = str[i];
        }
    }

    // printf("%s\n", palin);
    // printf("%lu\n", strlen(palin));

    int right = N-1;
    int j = 0;
    temp = right;
    int right_end;
    int flag = 0;

    // return 0;

    while(right >= 0 && flag == 0){
        // printf("%d %d\n", right, j);
        if(str[temp] == 'A' || str[temp] == 'C' || str[temp] == 'G' || str[temp] == 'T'){
            while(j < M/2){
                if(str[temp] == 'A' || str[temp] == 'C' || str[temp] == 'G' || str[temp] == 'T'){
                    if(palin[j] == str[temp]){
                    j++;
                    temp--;
                    if(j == M/2){
                        right_end = temp + 1;
                        flag = 1;
                        break;
                    }
                    }
                    else{
                        j = 0;
                        right--;
                        temp = right;
                        break;
                    }
                }
                else{
                    temp--;
                }
            }
        }
        else{
            right--;
            temp = right;
        }
    }

    // for(int k=right;k>=right_end;k--){
    //     printf("%c", str[k]);
    // }

    // printf("%d %d\n", right, right_end);

    i = 0;
    for(int k=right;k>=right_end;k--){
        if(str[k] == 'A') str[k] = 'T';
        else if(str[k] == 'T') str[k] = 'A';
        else if(str[k] == 'C') str[k] = 'G';
        else if(str[k] == 'G') str[k] = 'C';
    }

    for(int i=0;i<N;i++){
        if(str[i] == 'A' || str[i] == 'C' || str[i] == 'G' || str[i] == 'T'){
            printf("%c", str[i]);
        }
    }
}