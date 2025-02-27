#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr1;
    char c, filename[100];
    int line = 1, chars = 0;

    printf("Enter the name of the file : ");
    scanf("%s", filename);

    fptr1 = fopen(filename, "r");

    c = fgetc(fptr1);

    while (c != EOF)
    {
        if (c == '\n')
        {
            line++;
        }
        c = fgetc(fptr1);
        chars++;
    }

    printf("Total number of lines is : %d \n Total number of chars is : %d", line, chars);
    fclose(fptr1);
}