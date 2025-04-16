#include <stdio.h>
#include <string.h>
#include <math.h>
 
void encode(int key, int doc){
    int e = key ^ doc;
    
    // calculate length of key
    int m = floor(log2(key))+1;
    int n = floor(log2(doc))+1;

    int len = m > n ? m : n;
    
    int c = 0;
    for(int i=0;i<32;i++){
        if(e & 1<<i) c++;
    }

    printf("%d", c);

    int o = floor(log2(c))+1;

    for(int i=len-1;i>=o;i--){
        if(c & 1<<(i%o)) c |= 1<<i;
    }

    // printf("\n");
    // for(int i=0;i<len;i++){
    //     if(c & 1<<i) printf("1");
    //     else printf("0");
    // }
    // printf("\n");

    for(int i=len-1;i>=0;i--){
        if(c & 1<<i){
            if(doc & 1<<i) printf("1");
            else printf("0");
        }
        else{
            if(e & 1<<i) printf("1");
            else printf("0");
        }
    }
}
 
 
int main(int argc, char *argv[]) {
    int key, doc;
    scanf("%d", &key);
    scanf("%d", &doc);
    encode(key, doc);
 
    return 0;
}