#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum
{
    MAIN,
    INT,
    CHAR,
    L_PAREN,
    R_PAREN,
    ID,
    NUM,
    L_BRACE,
    R_BRACE,
    SEMI,
    COMMA,
    END,
    INVALID,
    COMMA,
    ASSIGN
} TokenType;

char token[100];
TokenType currTok;
FILE *fp;

int isKeyword(char *str)
{
    if (strcmp(str, "main") == 0)
        return MAIN;
    if (strcmp(str, "int") == 0)
        return INT;
    if (strcmp(str, "char") == 0)
        return CHAR;
}

TokenType getNextToken()
{
    int ch;
    while (ch = fgetc(fp) != EOF)
    {
        if (isspace(ch))
        {
            continue;
        }

        if (isalpha(ch))
        {
            int i = 0;
            token[i++] = ch;
            while (isalnum(ch = fgetc(fp)))
            {
                token[i++] = ch;
            }
            token[i] = '\0';
            ungetc(ch, fp);
            int kw = isKeyword(ch);
            if (kw)
            {
                return currTok = (TokenType)kw;
            }
            else
            {
                return currTok = ID;
            }
        }

        if (isdigit(ch))
        {
            return currTok = NUM;
        }
        token[0] = ch;
        token[1] = '\0';
        switch (ch)
        {
        case '(':
            return currTok = L_PAREN;
        case ')':
            return currTok = R_PAREN;
        case '{':
            return currTok = L_BRACE;
        case '}':
            return currTok = R_BRACE;
        case ',':
            return currTok = COMMA;
        case ';':
            return currTok = SEMI;
        case '=':
            return currTok = ASSIGN;
        }
        return currTok = INVALID;
    }
    return currTok = END;
}

void match(TokenType expected)
{
    if (currTok == expected)
    {
        currTok = getNextToken();
    }
    else
    {
        printf("error");
    }
}

void assign_stat()
{
    if (currTok == ID)
    {
        match(ID);
        match(ASSIGN);
        if (currTok == ID || currTok == NUM)
        {
            match(currTok);
        }
        else
        {
            exit(1);
        }
        match(SEMI);
    }
    else
    {
        exit(1);
    }
}