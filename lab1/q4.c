#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 10
#define MAX_PARAGRAPH_LENGTH 1000

int main() {
    char file1[100], file2[100];

    printf("Enter the name of the paragraph file (File 1): ");
    scanf("%s", file1);
    printf("Enter the name of the words file (File 2): ");
    scanf("%s", file2);

    FILE *f1 = fopen(file1, "r");
    if (!f1) {
        printf("Error opening file %s\n", file1);
        return 1;
    }

    char paragraph[MAX_PARAGRAPH_LENGTH];
    int i = 0;
    char c;
    while ((c = fgetc(f1)) != EOF && i < MAX_PARAGRAPH_LENGTH - 1) {
        paragraph[i++] = c;
    }
    paragraph[i] = '\0';
    fclose(f1);

    FILE *f2 = fopen(file2, "r");
    if (!f2) {
        printf("Error opening file %s\n", file2);
        return 1;
    }

    char word[MAX_WORD_LENGTH];
    for (int w = 0; w < MAX_WORDS; w++) {
        i = 0;
        while ((c = fgetc(f2)) != EOF && !isspace(c)) {
            word[i++] = c;
        }
        word[i] = '\0';

        int found = 0;
        char *ptr = paragraph;
        int index = 0;
        while ((ptr = strstr(ptr, word)) != NULL) {
            index = ptr - paragraph + 1;
            found = 1;
            printf("Word '%s' found at position %d in the paragraph.\n", word, index);
            ptr++;
        }

        if (!found) {
            printf("Word '%s' not found in the paragraph.\n", word);
        }

        if (c == EOF) break;
        while (isspace(c)) {
            c = fgetc(f2);
        }
    }

    fclose(f2);
    return 0;
}
