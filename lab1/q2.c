#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fp1,*fp2;
    char filename1[100],filename2[100],c;

    printf("Enter the name of the first file : ");
    scanf("%s",filename1);

    printf("Enter the name of the second file : ");
    scanf("%s",filename2);

    fp1 = fopen(filename1,"r");
    fp2 = fopen(filename2,"w+");

    if(!fp1){
        perror("Invalid File Name");
        exit(0);
    }

    fseek(fp1,0,SEEK_END);
    long size = ftell(fp1);

   

    for(long i = size;i>=0;i--){
        fseek(fp1,i,SEEK_SET);
        c = fgetc(fp1);
        fputc(c,fp2);
    }

    printf("\n Contents copied to %s \n",filename2);
    printf("Size of file : %ld \n \n",size);

    fclose(fp1);
    fclose(fp2);



}