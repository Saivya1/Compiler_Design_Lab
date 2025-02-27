#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ca;
char buf[256];
int row = 1;
int col = 1;

typedef struct token
{
    char TokName[100];
    int row, col;
    char type[50];

} token;

token getNextTok(FILE *fptr)
{

    token tok;
    tok.TokName[0] = '\0';
    tok.row = row;
    tok.col = col;

    ca = fgetc(fptr);

    if (ca == EOF)
    {
        strcpy(tok.TokName, "EOF");
        return tok;
    }

    while (ca != EOF)
    {
        int i = 0;
        buf[i] = '\0';

        if (ca == '=')
        {
            buf[i++] = ca;
            ca = fgetc(fptr);
            if (ca == '=')
            {
                buf[i++] = ca;
                buf[i] = '\0';
                strcpy(tok.TokName, buf);
                tok.row = row;
                tok.col = col;
                strcpy(tok.type, "RelOp");
                return tok;
            }
            else
            {
                buf[i] = '\0';
                strcpy(tok.TokName, buf);
                tok.row = row;
                tok.col = col;
                strcpy(tok.type, "AssgnOp");
                return tok;
            }
        }
        else if (ca == '&' || ca == '|')
        {
            char dup = ca;
            buf[i++] = ca;
            ca = fgetc(fptr);
            if (ca == dup)
            {
                buf[i++] = ca;
            }
            buf[i] = '\0';
            strcpy(tok.TokName, buf);
            tok.row = row;
            tok.col = col;
            strcpy(tok.type, "LogOp");
            return tok;
        }
        else if (ca == '<' || ca == '>' || ca == '!')
        {

            buf[i++] = ca;
            ca = fgetc(fptr);

            if (ca == '=')
            {
                buf[i++] = ca;
                buf[i] = '\0';
            }
            buf[i] = '\0';
            strcpy(tok.TokName, buf);
            tok.row = row;
            tok.col = col;
            strcpy(tok.type, "RelOp");
            return tok;
        }
        else
        {
            buf[i] = '\0';
            ca = fgetc(fptr);
        }
        col++;

        if (ca == '\n')
        {
            row++;
            col = 1;
        }
    }

    return tok;
}

int main()
{

    char fname[40];
    token temp;

    printf("Enter the name of the input file : ");
    scanf("%s", fname);

    FILE *fptr = fopen(fname, "r");

    if (fptr == NULL)
    {
        printf("Error");
        exit(0);
    }

    while (1)
    {
        temp = getNextTok(fptr);
        if (strcmp(temp.TokName, "EOF") == 0)
            break;

        printf("< %s , %d , %d , %s >\n", temp.TokName, temp.row, temp.col, temp.type);
    }

    fclose(fptr);
    return 0;
}