#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct token {
    char token_name[20];
    int row, col;
    char type[20];
    int index;
} token;

int main()
{
    token tok;
    char c, buf[20];
    int row = 1, col = 1;
    FILE *fp = fopen("digit.c", "r");
    FILE *out_fp = fopen("q1b_out", "w"); 

    if (fp == NULL) {
        printf("Cannot open file \n");
        exit(0);
    }

    if (out_fp == NULL) {
        printf("Cannot open output file \n");
        exit(0);
    }

    c = fgetc(fp);
    while (c != EOF) {
        int i = 0;
        buf[0] = '\0';

        if (c == '=' || c == '<' || c == '>' || c == '+' || c == '-' || c == '*' || c == '/') {
            buf[i++] = c;
            buf[i] = '\0';
            strcpy(tok.token_name, buf);
            tok.row = row;
            tok.col = col;
            strcpy(tok.type, "SpecialSymbol");
            fprintf(out_fp, "< %s, %d, %d, %s >\n", tok.token_name, tok.row, tok.col, tok.type);  // Write to file
        } else if (c == '"' || isalpha(c) || c == '_') {
            if (c == '"') {
                i = 0;
                c = fgetc(fp);
                while (c != '"' && c != EOF) {
                    buf[i++] = c;
                    c = fgetc(fp);
                }
                buf[i] = '\0';
                strcpy(tok.token_name, buf);
                tok.row = row;
                tok.col = col;
                strcpy(tok.type, "StringLiteral");
                fprintf(out_fp, "< %s, %d, %d, %s >\n", tok.token_name, tok.row, tok.col, tok.type);  // Write to file
            } else if (isalpha(c) || c == '_') {
                i = 0;
                while (isalnum(c) || c == '_') {
                    buf[i++] = c;
                    c = fgetc(fp);
                }
                buf[i] = '\0';
                strcpy(tok.token_name, buf);
                tok.row = row;
                tok.col = col;
                strcpy(tok.type, "Identifier");
                fprintf(out_fp, "< %s, %d, %d, %s >\n", tok.token_name, tok.row, tok.col, tok.type);  // Write to file
            }
        } else if (isdigit(c)) {
            i = 0;
            while (isdigit(c)) {
                buf[i++] = c;
                c = fgetc(fp);
            }
            if (c == '.') {
                buf[i++] = c;
                c = fgetc(fp);
                while (isdigit(c)) {
                    buf[i++] = c;
                    c = fgetc(fp);
                }
            }
            buf[i] = '\0';
            strcpy(tok.token_name, buf);
            tok.row = row;
            tok.col = col;
            strcpy(tok.type, "NumericConstant");
            fprintf(out_fp, "< %s, %d, %d, %s >\n", tok.token_name, tok.row, tok.col, tok.type);  // Write to file
        }

        c = fgetc(fp);
        col++;

        if (c == '\n') {
            row++;
            col = 1;
        }
    }

    fclose(fp);
    fclose(out_fp);  
    return 0;
}
