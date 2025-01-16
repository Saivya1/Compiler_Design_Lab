#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 32

const char *keywords[] = {
    "break", "case", "char","continue","do", "double", 
    "else","float", "for", "if","int", "long", 
    "return","signed","struct", "switch", "typedef", "void","while"
};


int is_keyword(char *word) {
    for (int i = 0; i < 18; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;  
}

void to_uppercase(char *word) {
    for (int i = 0; word[i]; i++) {
        word[i] = toupper(word[i]);
    }
}

int main() {
    FILE *fa, *fb;
    int ca;
    char word[MAX_LEN];
    int word_len = 0;

    
    fa = fopen("q1_code.c", "r");
    if (fa == NULL) {
        printf("Cannot open input file\n");
        exit(0);
    }

    
    fb = fopen("q3_code_out.c", "w");
    if (fb == NULL) {
        printf("Cannot open output file\n");
        fclose(fa);
        exit(0);
    }

    ca = getc(fa);  

    while (ca != EOF) {
        if (isalpha(ca) || ca == '_') {  
            word_len = 0;
            word[word_len++] = ca;
            ca = getc(fa);

            
            while ((isalnum(ca) || ca == '_') && ca != EOF) {
                word[word_len++] = ca;
                ca = getc(fa);
            }
            word[word_len] = '\0';  

            if (is_keyword(word)) {
                to_uppercase(word); 
                printf("%s \n",word); 
            }
            
            fputs(word, fb);  
        } else {
            
            putc(ca, fb);
            ca = getc(fa);
        }
    }

    fclose(fa);  
    fclose(fb);  

    return 0;
}
