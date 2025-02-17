#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr1, *fptr2;
    char filename[100], c;

    printf("Enter name of source file : ");
    scanf("%s", filename);

    fptr1 = fopen(filename, "r");

    printf("Enter name of source file : ");
    scanf("%s", filename);

    fptr2 = fopen(filename, "w+");

    c = fgetc(fptr1);

    while (c != EOF)
    {
        fputc(c, fptr2);
        c = fgetc(fptr1);
    }

    printf("Copied Successfully");
    fclose(fptr1);
    fclose(fptr2);
}