#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void decode(int key, int enc_doc) {
    // Extract count and encoded_bits (first digit)
    int count = 0;
    int temp = enc_doc;
    

    while (temp >= 10) {
        temp /= 10;
    }
    count = temp;
    // printf("count: %d\n",count);
    


    // Calculate length of key and encoded_bits
    int key_len = (int)log2(key) + 1;
    int enc_len = (int)log10(enc_doc);
    int len = (key_len > enc_len) ? key_len : enc_len;

    // printf("%d\n", len);
    int* e = (int*)malloc(sizeof(int) * len);
    int i = 0;
    temp = enc_doc;
    // printf("temp: %d\n",temp);
    while (temp >= 10) {
        e[i] = temp % 10;
        i++;
        temp /= 10;
    }

    // printf("e\n");
    // for(int i=0;i<len;i++){
    //     printf("%d",e[i]);
    // }
    // printf("\n");
    int k[len];
    i = 0;
    int temp_key = key;
    while(temp_key>0){
        k[i] = temp_key % 2;
        temp_key /= 2;
        i++;
    }

    // printf("key\n");

    // for(int i=0;i<len;i++){
    //     printf("%d",k[i]);
    // }

    // printf("\n");

    //print count bit
    // printf("count\n");
    // for(int i=0;i<len;i++){
    //     if(count & 1<<i) printf("1");
    //     else printf("0");
    // }
    // printf("\n");
    int doc = 0;

    // Reconstruct the original document
    for(int i=0;i<len;i++){
        if(count & 1<<i){
            if(e[i] == 1) doc |= 1<<i;
        }
        else{
            doc |= (e[i] ^ k[i])<<i;
        }
    }

    int hamming = 0;
    // printf("%d %d\n",key,doc);
    int t = key ^ doc;
    // printf("t: %d\n",t);
    for(int i=0;i<32;i++){
        if(t & 1<<i) hamming++;
    }

    // printf("%d\n",hamming);
    count -= hamming;

    while(count>0){
        doc = doc & ~(1<<(len-count));
        count--;
    }

    printf("%d\n", doc);
    
    // for (int i = 0; i < len; i++) {
    //     int bit = (encoded_bits >> i) & 1;
    //     if (count & (1 << (i % ((int)log2(count) + 1)))) {
    //         e |= (bit << i);
    //     } else {
    //         e |= ((bit ^ ((key >> i) & 1)) << i);
    //     }
    // }

    // for(int i=len-1;i>=0;i--){
    //     if(e & 1<<i) printf("1");
    //     else printf("0");
    // }
    // printf("\n");

    // Reconstruct the original document
    // doc = key ^ e;

    // printf("%d\n", e);
}

int main(int argc, char *argv[]) {
    int key, enc_doc;
    scanf("%d", &key);
    scanf("%d", &enc_doc);
    decode(key, enc_doc);

    return 0;
}