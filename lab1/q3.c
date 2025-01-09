#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp1, *fp2, *fp3;
    char filename1[100], filename2[100], filename3[100];
    char c1, c2;

    printf("Enter the name of file 1: ");
    scanf("%s", filename1);

    printf("Enter the name of file 2: ");
    scanf("%s", filename2);

    printf("Enter the name of file 3 (output file): ");
    scanf("%s", filename3);

    fp1 = fopen(filename1, "r");
    fp2 = fopen(filename2, "r");
    fp3 = fopen(filename3, "w+");

    if (!fp1 || !fp2) {
        perror("Invalid File Name");
        exit(1);
    }

    while (1) {
        while ((c1 = fgetc(fp1)) != EOF && c1 != '\n') {
            fputc(c1, fp3);
        }
        if (c1 != EOF) {
            fputc('\n', fp3);
        }

        while ((c2 = fgetc(fp2)) != EOF && c2 != '\n') {
            fputc(c2, fp3);
        }
        if (c2 != EOF) {
            fputc('\n', fp3);
        }

        if (c1 == EOF && c2 == EOF) {
            break;
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    return 0;
}
