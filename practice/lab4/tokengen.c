#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int row = 1, col = 1;
char buf[100];

char specialSymbol[] = {'?', ';', ':', ',', '(', ')', '{', '}', '.'};
char arithmeticSymbol[] = {'*', '+', '-', '/', '%'};
char *keyword[] = {"for", "if", "else", "while", "do", "break", "continue", "return", "int", "double", "float", "char",
                   "long", "short", "sizeof", "typedef", "switch", "case", "struct", "const", "void", "exit"};

typedef struct token
{
    char name[100];
    int row, col;
    char type[100];
} token;

int isSpecial(char word)
{
    for (int i = 0; i < sizeof(specialSymbol) / sizeof(specialSymbol[0]); i++)
        if (word == specialSymbol[i])
            return 1;
    return 0;
}

int isArithmetic(char word)
{
    for (int i = 0; i < sizeof(arithmeticSymbol) / sizeof(arithmeticSymbol[0]); i++)
        if (word == arithmeticSymbol[i])
            return 1;
    return 0;
}

int isKeyword(char *word)
{
    for (int i = 0; i < sizeof(keyword) / sizeof(keyword[0]); i++)
        if (strcmp(word, keyword[i]) == 0)
            return 1;
    return 0;
}

token getNext(FILE *fptr)
{
    token tok;
    tok.name[0] = '\0';
    tok.row = row;
    tok.col = col;
    tok.type[0] = '\0';

    char ca;
    int i = 0;

    while ((ca = fgetc(fptr)) != EOF)
    {
        col++;

        if (ca == ' ' || ca == '\t')
            continue;
        if (ca == '\n')
        {
            row++;
            col = 1;
            continue;
        }

        if (ca == '/')
        {
            char next = fgetc(fptr);
            if (next == '/')
            {
                while ((ca = fgetc(fptr)) != '\n' && ca != EOF)
                    ;
                row++;
                col = 1;
                continue;
            }
            else if (next == '*')
            {
                while (1)
                {
                    ca = fgetc(fptr);
                    if (ca == '*' && (ca = fgetc(fptr)) == '/')
                        break;
                    if (ca == '\n')
                    {
                        row++;
                        col = 1;
                    }
                }
                continue;
            }
            else
                ungetc(next, fptr);
        }

        if (isalpha(ca) || ca == '_')
        {
            i = 0;
            buf[i++] = ca;
            while ((ca = fgetc(fptr)) != EOF && (isalnum(ca) || ca == '_'))
            {
                buf[i++] = ca;
                col++;
            }
            buf[i] = '\0';
            ungetc(ca, fptr);

            strcpy(tok.name, buf);
            tok.row = row;
            tok.col = col - i;
            strcpy(tok.type, isKeyword(buf) ? "keyword" : "identifier");
            return tok;
        }

        if (isdigit(ca))
        {
            i = 0;
            buf[i++] = ca;
            while ((ca = fgetc(fptr)) != EOF && isdigit(ca))
            {
                buf[i++] = ca;
                col++;
            }
            buf[i] = '\0';
            ungetc(ca, fptr);

            strcpy(tok.name, buf);
            tok.row = row;
            tok.col = col - i;
            strcpy(tok.type, "number");
            return tok;
        }

        if (isArithmetic(ca))
        {
            tok.name[0] = ca;
            tok.name[1] = '\0';
            tok.row = row;
            tok.col = col;
            strcpy(tok.type, "arithmetic operator");
            return tok;
        }

        if (isSpecial(ca))
        {
            tok.name[0] = ca;
            tok.name[1] = '\0';
            tok.row = row;
            tok.col = col;
            strcpy(tok.type, "special symbol");
            return tok;
        }

        if (ca == '=' || ca == '!' || ca == '<' || ca == '>')
        {
            char next = fgetc(fptr);
            if (next == '=')
            {
                tok.name[0] = ca;
                tok.name[1] = '=';
                tok.name[2] = '\0';
                tok.row = row;
                tok.col = col - 1;
                strcpy(tok.type, "comparison operator");
                return tok;
            }
            else
            {
                ungetc(next, fptr);
                tok.name[0] = ca;
                tok.name[1] = '\0';
                tok.row = row;
                tok.col = col;
                strcpy(tok.type, (ca == '=') ? "assignment operator" : "comparison operator");
                return tok;
            }
        }

        if (ca == '&' || ca == '|')
        {
            char next = fgetc(fptr);
            if (next == ca)
            {
                tok.name[0] = ca;
                tok.name[1] = ca;
                tok.name[2] = '\0';
                tok.row = row;
                tok.col = col - 1;
                strcpy(tok.type, "logical operator");
                return tok;
            }
            else
            {
                ungetc(next, fptr);
            }
        }
    }

    strcpy(tok.name, "EOF");
    strcpy(tok.type, "end");
    return tok;
}

int main()
{
    token temp;
    char fname[100];

    printf("Enter the name of the file: ");
    scanf("%s", fname);

    FILE *fptr = fopen(fname, "r");
    if (!fptr)
    {
        printf("Error opening file!\n");
        return 1;
    }

    while (1)
    {
        temp = getNext(fptr);
        if (strcmp(temp.name, "EOF") == 0)
            break;
        printf("< %s , %d , %d , %s >\n", temp.name, temp.row, temp.col, temp.type);
    }

    fclose(fptr);
    return 0;
}
