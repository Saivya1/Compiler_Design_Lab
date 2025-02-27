/*

Assembly


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int row = 1, col = 1;
char buf[100];

// Define symbols specific to assembly language
char specialSymbol[] = {':', ',', '(', ')', '[', ']', '+'};
char *mnemonics[] = {"MOV", "ADD", "SUB", "MUL", "DIV", "JMP", "CMP", "JE", "JNE", "JGE", "JLE", "PUSH", "POP", "CALL", "RET"};
char *registers[] = {"AX", "BX", "CX", "DX", "SI", "DI", "SP", "BP"};
char *directives[] = {".data", ".code", ".text", "END"};

typedef struct token
{
    char name[100];
    int row, col;
    char type[100];
} token;

// Function to check if a character is a special symbol
int isSpecial(char word)
{
    for (int i = 0; i < sizeof(specialSymbol) / sizeof(specialSymbol[0]); i++)
        if (word == specialSymbol[i])
            return 1;
    return 0;
}

// Function to check if a word is a mnemonic (assembly instruction)
int isMnemonic(char *word)
{
    for (int i = 0; i < sizeof(mnemonics) / sizeof(mnemonics[0]); i++)
        if (strcmp(word, mnemonics[i]) == 0)
            return 1;
    return 0;
}

// Function to check if a word is a register
int isRegister(char *word)
{
    for (int i = 0; i < sizeof(registers) / sizeof(registers[0]); i++)
        if (strcmp(word, registers[i]) == 0)
            return 1;
    return 0;
}

// Function to check if a word is a directive
int isDirective(char *word)
{
    for (int i = 0; i < sizeof(directives) / sizeof(directives[0]); i++)
        if (strcmp(word, directives[i]) == 0)
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

        // Handle assembly comments (which start with ';')
        if (ca == ';')
        {
            while ((ca = fgetc(fptr)) != '\n' && ca != EOF)
                ;
            row++;
            col = 1;
            continue;
        }

        // Identify labels (identifiers ending with ':')
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

            if (isMnemonic(buf))
                strcpy(tok.type, "mnemonic");
            else if (isRegister(buf))
                strcpy(tok.type, "register");
            else if (isDirective(buf))
                strcpy(tok.type, "directive");
            else
                strcpy(tok.type, "identifier");
            return tok;
        }

        // Handle numbers (operands)
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

        // Handle special symbols
        if (isSpecial(ca))
        {
            tok.name[0] = ca;
            tok.name[1] = '\0';
            tok.row = row;
            tok.col = col;
            strcpy(tok.type, "special symbol");
            return tok;
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
*/

// JAVA

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

// int row = 1, col = 1;
// char buf[100];

// // Define symbols specific to Java
// char specialSymbol[] = {';', ',', '(', ')', '{', '}', '.'};
// char *keywords[] = {"class", "public", "private", "protected", "static", "void", "int", "double", "float", "char",
//                     "long", "short", "boolean", "if", "else", "while", "for", "do", "switch", "case", "break", "continue", "return"};
// char *operators[] = {"+", "-", "*", "/", "%", "=", "==", "!=", "<", "<=", ">", ">=", "&&", "||", "!"};

// typedef struct token
// {
//     char name[100];
//     int row, col;
//     char type[100];
// } token;

// // Function to check if a character is a special symbol
// int isSpecial(char word)
// {
//     for (int i = 0; i < sizeof(specialSymbol) / sizeof(specialSymbol[0]); i++)
//         if (word == specialSymbol[i]) return 1;
//     return 0;
// }

// // Function to check if a word is a keyword
// int isKeyword(char *word)
// {
//     for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
//         if (strcmp(word, keywords[i]) == 0) return 1;
//     return 0;
// }

// // Function to check if a word is an operator
// int isOperator(char *word)
// {
//     for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); i++)
//         if (strcmp(word, operators[i]) == 0) return 1;
//     return 0;
// }

// token getNext(FILE *fptr)
// {
//     token tok;
//     tok.name[0] = '\0';
//     tok.row = row;
//     tok.col = col;
//     tok.type[0] = '\0';

//     char ca;
//     int i = 0;

//     while ((ca = fgetc(fptr)) != EOF)
//     {
//         col++;

//         if (ca == ' ' || ca == '\t') continue;
//         if (ca == '\n') { row++; col = 1; continue; }

//         // Handle Java comments (single-line and multi-line)
//         if (ca == '/') {
//             char next = fgetc(fptr);
//             if (next == '/') {
//                 while ((ca = fgetc(fptr)) != '\n' && ca != EOF);
//                 row++; col = 1;
//                 continue;
//             } else if (next == '*') {
//                 while (1) {
//                     ca = fgetc(fptr);
//                     if (ca == '*' && (ca = fgetc(fptr)) == '/')
//                         break;
//                     if (ca == '\n') { row++; col = 1; }
//                 }
//                 continue;
//             } else ungetc(next, fptr);
//         }

//         // Identify identifiers and keywords
//         if (isalpha(ca) || ca == '_') {
//             i = 0;
//             buf[i++] = ca;
//             while ((ca = fgetc(fptr)) != EOF && (isalnum(ca) || ca == '_')) {
//                 buf[i++] = ca;
//                 col++;
//             }
//             buf[i] = '\0';
//             ungetc(ca, fptr);

//             strcpy(tok.name, buf);
//             tok.row = row;
//             tok.col = col - i;
//             strcpy(tok.type, isKeyword(buf) ? "keyword" : "identifier");
//             return tok;
//         }

//         // Handle numbers
//         if (isdigit(ca)) {
//             i = 0;
//             buf[i++] = ca;
//             while ((ca = fgetc(fptr)) != EOF && isdigit(ca)) {
//                 buf[i++] = ca;
//                 col++;
//             }
//             buf[i] = '\0';
//             ungetc(ca, fptr);

//             strcpy(tok.name, buf);
//             tok.row = row;
//             tok.col = col - i;
//             strcpy(tok.type, "number");
//             return tok;
//         }

//         // Handle operators
//         if (strchr("+-*/%=!<>&|", ca)) {
//             i = 0;
//             buf[i++] = ca;
//             char next = fgetc(fptr);
//             if (strchr("=|&", next)) buf[i++] = next;
//             else ungetc(next, fptr);
//             buf[i] = '\0';

//             strcpy(tok.name, buf);
//             tok.row = row;
//             tok.col = col - i;
//             strcpy(tok.type, "operator");
//             return tok;
//         }

//         // Handle special symbols
//         if (isSpecial(ca)) {
//             tok.name[0] = ca;
//             tok.name[1] = '\0';
//             tok.row = row;
//             tok.col = col;
//             strcpy(tok.type, "special symbol");
//             return tok;
//         }
//     }

//     strcpy(tok.name, "EOF");
//     strcpy(tok.type, "end");
//     return tok;
// }

// int main()
// {
//     token temp;
//     char fname[100];

//     printf("Enter the name of the file: ");
//     scanf("%s", fname);

//     FILE *fptr = fopen(fname, "r");
//     if (!fptr) {
//         printf("Error opening file!\n");
//         return 1;
//     }

//     while (1) {
//         temp = getNext(fptr);
//         if (strcmp(temp.name, "EOF") == 0) break;
//         printf("< %s , %d , %d , %s >\n", temp.name, temp.row, temp.col, temp.type);
//     }

//     fclose(fptr);
//     return 0;
// }

// FORTRAN

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

// int row = 1, col = 1;
// char buf[100];

// // Define symbols specific to Fortran
// char specialSymbol[] = {'(', ')', ',', '=', '+', '-', '*', '/'};
// char *keywords[] = {"PROGRAM", "END", "INTEGER", "REAL", "DOUBLE PRECISION", "CHARACTER", "IF", "THEN", "ELSE", "ENDIF", "DO", "CONTINUE", "STOP"};
// char *operators[] = {"+", "-", "*", "/", "=", ".EQ.", ".NE.", ".LT.", ".LE.", ".GT.", ".GE.", ".AND.", ".OR.", ".NOT."};

// typedef struct token
// {
//     char name[100];
//     int row, col;
//     char type[100];
// } token;

// // Function to check if a character is a special symbol
// int isSpecial(char word)
// {
//     for (int i = 0; i < sizeof(specialSymbol) / sizeof(specialSymbol[0]); i++)
//         if (word == specialSymbol[i]) return 1;
//     return 0;
// }

// // Function to check if a word is a keyword
// int isKeyword(char *word)
// {
//     for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
//         if (strcmp(word, keywords[i]) == 0) return 1;
//     return 0;
// }

// // Function to check if a word is an operator
// int isOperator(char *word)
// {
//     for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); i++)
//         if (strcmp(word, operators[i]) == 0) return 1;
//     return 0;
// }

// token getNext(FILE *fptr)
// {
//     token tok;
//     tok.name[0] = '\0';
//     tok.row = row;
//     tok.col = col;
//     tok.type[0] = '\0';

//     char ca;
//     int i = 0;

//     while ((ca = fgetc(fptr)) != EOF)
//     {
//         col++;

//         if (ca == ' ' || ca == '\t') continue;
//         if (ca == '\n') { row++; col = 1; continue; }

//         // Handle Fortran comments (! indicates a comment)
//         if (ca == '!') {
//             while ((ca = fgetc(fptr)) != '\n' && ca != EOF);
//             row++; col = 1;
//             continue;
//         }

//         // Identify identifiers and keywords
//         if (isalpha(ca)) {
//             i = 0;
//             buf[i++] = ca;
//             while ((ca = fgetc(fptr)) != EOF && (isalnum(ca) || ca == '_')) {
//                 buf[i++] = ca;
//                 col++;
//             }
//             buf[i] = '\0';
//             ungetc(ca, fptr);

//             strcpy(tok.name, buf);
//             tok.row = row;
//             tok.col = col - i;
//             strcpy(tok.type, isKeyword(buf) ? "keyword" : "identifier");
//             return tok;
//         }

//         // Handle numbers
//         if (isdigit(ca)) {
//             i = 0;
//             buf[i++] = ca;
//             while ((ca = fgetc(fptr)) != EOF && isdigit(ca)) {
//                 buf[i++] = ca;
//                 col++;
//             }
//             buf[i] = '\0';
//             ungetc(ca, fptr);

//             strcpy(tok.name, buf);
//             tok.row = row;
//             tok.col = col - i;
//             strcpy(tok.type, "number");
//             return tok;
//         }

//         // Handle operators
//         if (strchr("+-*/=.", ca)) {
//             i = 0;
//             buf[i++] = ca;
//             char next = fgetc(fptr);
//             if (strchr("=.", next)) buf[i++] = next;
//             else ungetc(next, fptr);
//             buf[i] = '\0';

//             strcpy(tok.name, buf);
//             tok.row = row;
//             tok.col = col - i;
//             strcpy(tok.type, "operator");
//             return tok;
//         }

//         // Handle special symbols
//         if (isSpecial(ca)) {
//             tok.name[0] = ca;
//             tok.name[1] = '\0';
//             tok.row = row;
//             tok.col = col;
//             strcpy(tok.type, "special symbol");
//             return tok;
//         }
//     }

//     strcpy(tok.name, "EOF");
//     strcpy(tok.type, "end");
//     return tok;
// }

// int main()
// {
//     token temp;
//     char fname[100];

//     printf("Enter the name of the file: ");
//     scanf("%s", fname);

//     FILE *fptr = fopen(fname, "r");
//     if (!fptr) {
//         printf("Error opening file!\n");
//         return 1;
//     }

//     while (1) {
//         temp = getNext(fptr);
//         if (strcmp(temp.name, "EOF") == 0) break;
//         printf("< %s , %d , %d , %s >\n", temp.name, temp.row, temp.col, temp.type);
//     }

//     fclose(fptr);
//     return 0;
// }

// PERL

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

// int row = 1, col = 1;
// char buf[100];

// // Define symbols specific to Perl
// char specialSymbol[] = {'(', ')', ',', '=', '+', '-', '*', '/', ';'};
// char *keywords[] = {"sub", "my", "our", "use", "if", "elsif", "else", "while", "for", "foreach", "do", "last", "next", "redo", "goto", "return", "package", "require", "eval"};
// char *operators[] = {"+", "-", "*", "/", "=", "==", "!=", "<", "<=", ">", ">=", "eq", "ne", "lt", "le", "gt", "ge"};

// typedef struct token
// {
//     char name[100];
//     int row, col;
//     char type[100];
// } token;

// // Function to check if a character is a special symbol
// int isSpecial(char word)
// {
//     for (int i = 0; i < sizeof(specialSymbol) / sizeof(specialSymbol[0]); i++)
//         if (word == specialSymbol[i]) return 1;
//     return 0;
// }

// // Function to check if a word is a keyword
// int isKeyword(char *word)
// {
//     for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
//         if (strcmp(word, keywords[i]) == 0) return 1;
//     return 0;
// }

// // Function to check if a word is an operator
// int isOperator(char *word)
// {
//     for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); i++)
//         if (strcmp(word, operators[i]) == 0) return 1;
//     return 0;
// }

// token getNext(FILE *fptr)
// {
//     token tok;
//     tok.name[0] = '\0';
//     tok.row = row;
//     tok.col = col;
//     tok.type[0] = '\0';

//     char ca;
//     int i = 0;

//     while ((ca = fgetc(fptr)) != EOF)
//     {
//         col++;

//         if (ca == ' ' || ca == '\t') continue;
//         if (ca == '\n') { row++; col = 1; continue; }

//         // Handle Perl comments (# indicates a comment)
//         if (ca == '#') {
//             while ((ca = fgetc(fptr)) != '\n' && ca != EOF);
//             row++; col = 1;
//             continue;
//         }

//         // Identify identifiers and keywords
//         if (isalpha(ca) || ca == '$' || ca == '@' || ca == '%') {
//             i = 0;
//             buf[i++] = ca;
//             while ((ca = fgetc(fptr)) != EOF && (isalnum(ca) || ca == '_')) {
//                 buf[i++] = ca;
//                 col++;
//             }
//             buf[i] = '\0';
//             ungetc(ca, fptr);

//             strcpy(tok.name, buf);
//             tok.row = row;
//             tok.col = col - i;
//             strcpy(tok.type, isKeyword(buf) ? "keyword" : "identifier");
//             return tok;
//         }

//         // Handle numbers
//         if (isdigit(ca)) {
//             i = 0;
//             buf[i++] = ca;
//             while ((ca = fgetc(fptr)) != EOF && isdigit(ca)) {
//                 buf[i++] = ca;
//                 col++;
//             }
//             buf[i] = '\0';
//             ungetc(ca, fptr);

//             strcpy(tok.name, buf);
//             tok.row = row;
//             tok.col = col - i;
//             strcpy(tok.type, "number");
//             return tok;
//         }

//         // Handle operators
//         if (strchr("+-*/=<>", ca)) {
//             i = 0;
//             buf[i++] = ca;
//             char next = fgetc(fptr);
//             if (strchr("=<>", next)) buf[i++] = next;
//             else ungetc(next, fptr);
//             buf[i] = '\0';

//             strcpy(tok.name, buf);
//             tok.row = row;
//             tok.col = col - i;
//             strcpy(tok.type, "operator");
//             return tok;
//         }

//         // Handle special symbols
//         if (isSpecial(ca)) {
//             tok.name[0] = ca;
//             tok.name[1] = '\0';
//             tok.row = row;
//             tok.col = col;
//             strcpy(tok.type, "special symbol");
//             return tok;
//         }
//     }

//     strcpy(tok.name, "EOF");
//     strcpy(tok.type, "end");
//     return tok;
// }

// int main()
// {
//     token temp;
//     char fname[100];

//     printf("Enter the name of the file: ");
//     scanf("%s", fname);

//     FILE *fptr = fopen(fname, "r");
//     if (!fptr) {
//         printf("Error opening file!\n");
//         return 1;
//     }

//     while (1) {
//         temp = getNext(fptr);
//         if (strcmp(temp.name, "EOF") == 0) break;
//         printf("< %s , %d , %d , %s >\n", temp.name, temp.row, temp.col, temp.type);
//     }

//     fclose(fptr);
//     return 0;
// }
