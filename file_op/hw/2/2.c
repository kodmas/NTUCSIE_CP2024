#include "stdio.h"
#include "stdlib.h"

#define MOD (1<<30)

int main(){
    int N;
    scanf("%d", &N);

    char **files = (char**)malloc(N * sizeof(char*));
    for(int i = 0; i < N; i++){
        files[i] = (char*)malloc(100 * sizeof(char));
        scanf("%s", files[i]);
    }

    char type;
    int cur_data = 0;
    int cur_hash = 0;
    int nonce = 0;

    int invalid_block = -1;

    for(int i=0;i<N;i++){
        FILE *file = fopen(files[i], "r");
        
        char line[100];
        int data_num = 0;

        while(fgets(line, 100, file) != NULL){
            printf("%d\n", cur_hash);
            sscanf(line, "%c: %d", &type, &cur_data);
            // printf("%c %d\n", type, cur_data);
            // printf("data_num %d\n", data_num);
            if(type == 'P'){
                if(i == 0) {
                    data_num++;
                    continue;
                }
                else{
                    if(cur_hash != cur_data) {
                        invalid_block = i;
                        break;
                    }
                    else{
                        data_num++;
                        cur_hash = 0;
                    }
                }
            }
            else{
                // printf("before %d\n", cur_hash);
                // printf("cur_data %d\n", cur_data);
                // printf("expected %d\n", cur_hash ^ cur_data);
                if(data_num % 25 != 0) {
                    cur_hash = (cur_hash ^ cur_data) % MOD;
                    // printf("here\n");
                }
                else cur_hash = ((cur_hash ^ cur_data) << 1)% MOD;
                // printf("after %d\n", cur_hash);
                data_num++;
            }
        }

        // printf("%d\n", cur_hash);

        if(invalid_block != -1){
            printf("%d", invalid_block);
            break;
        }
        fclose(file);
    }

    if(invalid_block == -1) printf("-1");
}