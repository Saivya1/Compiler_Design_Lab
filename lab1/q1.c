#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fp1;
    char filename[100],c;

    printf("Enter the name of the file : ");
    scanf("%s",filename);

    fp1 = fopen(filename,"r");

    if(fp1==NULL){
        perror("Invalid File Name");
        exit(0);
    }

    int ctr=0;
    int sctr=1;
    c = fgetc(fp1);

    while(c != EOF){
        ctr++;
        c = fgetc(fp1);
        if(c == '\n'){
            sctr++;
        }
    }

    fclose(fp1);

    printf("Number of chars : %d \n",ctr);
    printf("Number of lines : %d \n",sctr);
}