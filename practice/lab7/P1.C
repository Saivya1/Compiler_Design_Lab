#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
    MAIN = 1,
    INT,
    CHAR,
    ID,
    NUM,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    COMMA,
    SEMI,
    ASSIGN,
    END,
    INVALID
} TokenType;

char token[100];
TokenType currentToken;
FILE *fp;

int isKeyword(const char *str)
{
    if (strcmp(str, "main") == 0)
        return MAIN;
    if (strcmp(str, "int") == 0)
        return INT;
    if (strcmp(str, "char") == 0)
        return CHAR;
    return 0;
}

TokenType getNextToken()
{
    int ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (isspace(ch))
            continue;

        if (isalpha(ch))
        {
            int i = 0;
            token[i++] = ch;
            while (isalnum(ch = fgetc(fp)))
                token[i++] = ch;
            token[i] = '\0';
            ungetc(ch, fp);
            int kw = isKeyword(token);
            if (kw)
                return currentToken = (TokenType)kw;
            else
                return currentToken = ID;
        }

        if (isdigit(ch))
        {
            int i = 0;
            token[i++] = ch;
            while (isdigit(ch = fgetc(fp)))
                token[i++] = ch;
            token[i] = '\0';
            ungetc(ch, fp);
            return currentToken = NUM;
        }

        token[0] = ch;
        token[1] = '\0';
        switch (ch)
        {
        case '(':
            return currentToken = LPAREN;
        case ')':
            return currentToken = RPAREN;
        case '{':
            return currentToken = LBRACE;
        case '}':
            return currentToken = RBRACE;
        case ',':
            return currentToken = COMMA;
        case ';':
            return currentToken = SEMI;
        case '=':
            return currentToken = ASSIGN;
        }
        return currentToken = INVALID;
    }
    return currentToken = END;
}

void match(TokenType expected)
{
    if (currentToken == expected)
        currentToken = getNextToken();
    else
    {
        printf("Syntax Error! Unexpected token: %s\n", token);
        exit(1);
    }
}

void identifier_list();

void assign_stat()
{
    if (currentToken == ID)
    {
        match(ID);
        match(ASSIGN);
        if (currentToken == ID || currentToken == NUM)
            match(currentToken);
        else
        {
            printf("Expected ID or NUM\n");
            exit(1);
        }
        match(SEMI);
    }
    else
    {
        printf("Expected ID at assignment\n");
        exit(1);
    }
}

void declarations()
{
    if (currentToken == INT || currentToken == CHAR)
    {
        match(currentToken); // data_type
        identifier_list();
        match(SEMI);
        declarations(); // recursion for next declaration
    }
    // else epsilon, do nothing
}

void identifier_list()
{
    match(ID);
    if (currentToken == COMMA)
    {
        match(COMMA);
        identifier_list();
    }
}

void Program()
{
    match(MAIN);
    match(LPAREN);
    match(RPAREN);
    match(LBRACE);
    declarations();
    assign_stat();
    match(RBRACE);
    if (currentToken == END)
        printf("Parsing successful!\n");
    else
        printf("Unexpected token after program end\n");
}

int main()
{
    char filename[100];
    printf("Enter input file name: ");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if (!fp)
    {
        printf("File not found!\n");
        return 1;
    }
    currentToken = getNextToken();
    Program();
    fclose(fp);
    return 0;
}
