#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
int main(void){
    char filename[20]={},buf[1025]={};
    scanf("%s",filename);
    filename[strlen(filename)]='\0';
    FILE *fp;
    if(strcmp(filename,"exit")==0) return 0;
    else fp=fopen(filename,"a+");
    getchar();
    while(1){
        char command[10];
        fgets(command, sizeof(command), stdin);
        command[strcspn(command,"\n")] = '\0';
        if(strcmp(command,"exit")==0){
            fclose(fp);
            break;
        }
        else if(strcmp(command,"close")==0){
            fclose(fp);
            buf[0]='\0';
            scanf("%s",filename);
            filename[strlen(filename)]='\0';
            getchar();
            if(strcmp(filename,"exit")==0) break;
            else fp=fopen(filename,"a+");
        }
        else if(strncmp(command,"add ",4)==0){
            int n=atoi(&command[4]);
            for(int i=0;i<n;i++){
                fgets(buf+strlen(buf),128,stdin);
                //printf("check:%s",buf);
            }
        }
        else if(strcmp(command,"clear")==0){
            buf[0]='\0';
        }
        else if(strcmp(command,"status")==0){
            printf("%s",buf);
        }
        else if(strcmp(command,"push")==0){
            fputs(buf,fp);
            fflush(fp);
            buf[0]='\0';
        }
        else if(strcmp(command,"pull")==0){
            fseek(fp,0,SEEK_SET);
            char pbuf[128]={};
            fgets(pbuf,128,fp);
            while(!feof(fp)){
                printf("%s",pbuf);
                fgets(pbuf,128,fp);
            }
        }
        else if(strcmp(command,"truncate")==0){
            fclose(fp);
            fp=fopen(filename,"w");
            fclose(fp);
            fp=fopen(filename,"a+");
            printf("File truncated.\n");
        }
        else printf("Invalid command.\n");
    }
    return 0;
}