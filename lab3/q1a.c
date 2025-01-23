#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct token {
    char token_name[10];
    int row, col;
    char type[10];
    int index;
} token;

int main()
{
    token tok;
    char c, buf[10];
    int row = 1, col = 1;
    FILE *fp = fopen("digit.c", "r");
    FILE *out_fp = fopen("q1a_out", "w");

    if (fp == NULL)
    {
        printf("Cannot open input file \n");
        exit(0);
    }

    if (out_fp == NULL)
    {
        printf("Cannot open output file \n");
        exit(0);
    }

    c = fgetc(fp);
    while (c != EOF)
    {
        int i = 0;
        buf[0] = '\0';

        if (c == '=')
        {
            buf[i++] = c;
            c = fgetc(fp);
            if (c == '=')
            {
                buf[i++] = c;
                buf[i] = '\0';
                strcpy(tok.token_name, buf);
                tok.row = row;
                tok.col = col;
                strcpy(tok.type, "RelOP");
                fprintf(out_fp, "< %s, %d, %d, %s >\n", tok.token_name, tok.row, tok.col, tok.type);
            }
            else
            {
                buf[i] = '\0';
                strcpy(tok.token_name, buf);
                tok.row = row;
                tok.col = col;
                strcpy(tok.type, "AssignOP");
                fprintf(out_fp, "< %s, %d, %d, %s >\n", tok.token_name, tok.row, tok.col, tok.type);
            }
        }
        else if (c == '&' || c == '|' || c == '!')
        {
            buf[i++] = c;
            char dup = c;
            c = fgetc(fp);

            if (c == dup)
            {
                buf[i++] = c;
            }
            buf[i] = '\0';
            strcpy(tok.token_name, buf);
            tok.row = row;
            tok.col = col;
            strcpy(tok.type, "LogOP");
            fprintf(out_fp, "< %s, %d, %d, %s >\n", tok.token_name, tok.row, tok.col, tok.type);
        }
        else if (c == '<' || c == '>' || c == '!')
        {
            buf[i++] = c;
            c = fgetc(fp);

            if (c == '=')
            {
                buf[i++] = c;
            }
            buf[i] = '\0';
            strcpy(tok.token_name, buf);
            tok.row = row;
            tok.col = col;
            strcpy(tok.type, "RelOP");
            fprintf(out_fp, "< %s, %d, %d, %s >\n", tok.token_name, tok.row, tok.col, tok.type);
        }
        else
        {
            buf[i] = '\0';
        }

        c = fgetc(fp);
        col++;

        if (c == '\n')
        {
            row++;
            col = 1;
        }
    }

    fclose(fp);
    fclose(out_fp);
    return 0;
}
