// ASSEMBLY
//  #include <stdio.h>
//  #include <stdlib.h>
//  #include <string.h>
//  #include <ctype.h>

// #define MAX_TOKENS 1024
// #define MAX_SYMBOLS 256

// // Structure to store tokens
// struct token
// {
//     char lexeme[64]; // Token text
//     int row, col;    // Position in source code
//     char type[30];   // Token type (Instruction, Register, Label, etc.)
// };

// // Structure for symbol table entries
// struct symbol
// {
//     int index;
//     char name[64];
//     char type[30];
//     int address;
// };

// int row = 1, col = 1; // Track line and column numbers

// // Function to get the next token from the input file
// struct token getNextToken(FILE *fin)
// {
//     struct token t;
//     t.row = -1;
//     char c;
//     while ((c = getc(fin)) != EOF)
//     {
//         if (c == '\n')
//         {
//             row++;
//             col = 1;
//             continue;
//         }
//         if (isspace(c))
//         {
//             col++;
//             continue;
//         }

//         // Handling comments (Assuming `;` starts a comment)
//         if (c == ';')
//         {
//             while ((c = getc(fin)) != EOF && c != '\n')
//                 col++;
//             row++;
//             col = 1;
//             continue;
//         }

//         // Detect Labels (Identifiers ending with ':')
//         if (isalpha(c) || c == '_')
//         {
//             int startCol = col, startRow = row;
//             char ident[64];
//             int i = 0;
//             ident[i++] = c;
//             col++;
//             while ((c = getc(fin)) != EOF && (isalnum(c) || c == '_'))
//             {
//                 ident[i++] = c;
//                 col++;
//             }
//             if (c == ':')
//             {
//                 ident[i++] = ':';
//                 ident[i] = '\0';
//                 t.row = startRow;
//                 t.col = startCol;
//                 strcpy(t.lexeme, ident);
//                 strcpy(t.type, "Label");
//                 return t;
//             }
//             ident[i] = '\0';
//             ungetc(c, fin);
//             t.row = startRow;
//             t.col = startCol;
//             strcpy(t.lexeme, ident);
//             strcpy(t.type, "Instruction"); // Assume it's an instruction
//             return t;
//         }

//         // Detect Registers (e.g., `AX`, `BX`, `CX`, `DX`)
//         if (c == 'A' || c == 'B' || c == 'C' || c == 'D')
//         {
//             int startCol = col, startRow = row;
//             char reg[3] = {c, getc(fin), '\0'};
//             if (strcmp(reg, "AX") == 0 || strcmp(reg, "BX") == 0 ||
//                 strcmp(reg, "CX") == 0 || strcmp(reg, "DX") == 0)
//             {
//                 t.row = startRow;
//                 t.col = startCol;
//                 strcpy(t.lexeme, reg);
//                 strcpy(t.type, "Register");
//                 col += 2;
//                 return t;
//             }
//             ungetc(reg[1], fin);
//         }

//         // Detect Numbers (Immediate values)
//         if (isdigit(c))
//         {
//             int startCol = col, startRow = row;
//             char num[64];
//             int i = 0;
//             num[i++] = c;
//             col++;
//             while ((c = getc(fin)) != EOF && isdigit(c))
//             {
//                 num[i++] = c;
//                 col++;
//             }
//             num[i] = '\0';
//             ungetc(c, fin);
//             t.row = startRow;
//             t.col = startCol;
//             strcpy(t.lexeme, num);
//             strcpy(t.type, "Number");
//             return t;
//         }
//     }
//     t.row = -1;
//     return t;
// }

// int main()
// {
//     FILE *fin = fopen("input.asm", "r");
//     if (!fin)
//     {
//         printf("Error opening file.\n");
//         return 1;
//     }

//     struct symbol symTable[MAX_SYMBOLS];
//     int symCount = 0;

//     struct token t;
//     int address = 0;
//     while ((t = getNextToken(fin)).row != -1)
//     {
//         printf("<%s, %d, %d, %s>\n", t.type, t.row, t.col, t.lexeme);

//         if (strcmp(t.type, "Label") == 0)
//         {
//             strcpy(symTable[symCount].name, t.lexeme);
//             strcpy(symTable[symCount].type, "Label");
//             symTable[symCount].index = symCount;
//             symTable[symCount].address = address;
//             symCount++;
//         }
//         else if (strcmp(t.type, "Instruction") == 0)
//         {
//             address += 4;
//         }
//     }

//     fclose(fin);

//     // Print the symbol table
//     printf("\nSymbol Table:\n");
//     printf("Index\tName\tType\tAddress\n");
//     printf("-----\t----\t----\t-------\n");
//     for (int i = 0; i < symCount; i++)
//     {
//         printf("%d\t%s\t%s\t%d\n", symTable[i].index, symTable[i].name,
//                symTable[i].type, symTable[i].address);
//     }
//     return 0;
// }

// JAVA

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

// #define MAX_TOKENS 1024
// #define MAX_SYMBOLS 256

// struct token {
//     char lexeme[64];
//     int row, col;
//     char type[30];
// };

// struct symbol {
//     int index;
//     char name[64];
//     char type[30];
//     int size;
// };

// int row = 1, col = 1;

// struct token getNextToken(FILE *fin) {
//     struct token t;
//     t.row = -1;
//     char c;
//     while ((c = getc(fin)) != EOF) {
//         if (c == '\n') {
//             row++;
//             col = 1;
//             continue;
//         }
//         if (isspace(c)) {
//             col++;
//             continue;
//         }
//         if (isalpha(c) || c == '_') {
//             int startCol = col;
//             char ident[64];
//             int i = 0;
//             ident[i++] = c;
//             col++;
//             while ((c = getc(fin)) != EOF && (isalnum(c) || c == '_')) {
//                 ident[i++] = c;
//                 col++;
//             }
//             ident[i] = '\0';
//             if (c != EOF) {
//                 ungetc(c, fin);
//                 col--;
//             }
//             t.row = row;
//             t.col = startCol;
//             strcpy(t.lexeme, ident);
//             const char *keywords[] = {"int", "char", "float", "double", "long", "short", "if", "else", "for", "while", "return"};
//             int isKeyword = 0;
//             for (int j = 0; j < sizeof(keywords) / sizeof(keywords[0]); j++) {
//                 if (strcmp(ident, keywords[j]) == 0) {
//                     isKeyword = 1;
//                     break;
//                 }
//             }
//             if (isKeyword)
//                 strcpy(t.type, "Keyword");
//             else
//                 strcpy(t.type, "Identifier");
//             return t;
//         }
//     }
//     t.row = -1;
//     return t;
// }

// int main() {
//     FILE *fin = fopen("input.java", "r");
//     if (!fin) {
//         printf("Error opening file.\n");
//         return 1;
//     }

//     struct symbol symTable[MAX_SYMBOLS];
//     int symCount = 0;
//     int inDeclaration = 0;
//     char currentType[30] = "";

//     struct token t;
//     while ((t = getNextToken(fin)).row != -1) {
//         if (strcmp(t.type, "Keyword") == 0 && (strcmp(t.lexeme, "int") == 0 || strcmp(t.lexeme, "char") == 0 || strcmp(t.lexeme, "float") == 0 || strcmp(t.lexeme, "double") == 0 || strcmp(t.lexeme, "long") == 0 || strcmp(t.lexeme, "short") == 0)) {
//             inDeclaration = 1;
//             strcpy(currentType, t.lexeme);
//             continue;
//         }
//         if (inDeclaration) {
//             if (strcmp(t.type, "Identifier") == 0) {
//                 int exists = 0;
//                 for (int i = 0; i < symCount; i++) {
//                     if (strcmp(symTable[i].name, t.lexeme) == 0) {
//                         exists = 1;
//                         break;
//                     }
//                 }
//                 if (!exists && symCount < MAX_SYMBOLS) {
//                     symTable[symCount].index = symCount;
//                     strcpy(symTable[symCount].name, t.lexeme);
//                     strcpy(symTable[symCount].type, currentType);
//                     symCount++;
//                 }
//             }
//             if (strcmp(t.lexeme, ";") == 0) {
//                 inDeclaration = 0;
//                 currentType[0] = '\0';
//             }
//         }
//     }

//     fclose(fin);

//     printf("\nSymbol Table:\n");
//     printf("Index\tName\tType\n");
//     printf("-----\t----\t----\n");
//     for (int i = 0; i < symCount; i++) {
//         printf("%d\t%s\t%s\n", symTable[i].index, symTable[i].name, symTable[i].type);
//     }
//     return 0;
// }

// FORTRAN

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

// #define MAX_TOKENS 1024
// #define MAX_SYMBOLS 256

// struct token {
//     char lexeme[64];
//     int row, col;
//     char type[30];
// };

// struct symbol {
//     int index;
//     char name[64];
//     char type[30];
//     int size;
// };

// int row = 1, col = 1;

// struct token getNextToken(FILE *fin) {
//     struct token t;
//     t.row = -1;
//     char c;
//     while ((c = getc(fin)) != EOF) {
//         if (c == '\n') {
//             row++;
//             col = 1;
//             continue;
//         }
//         if (isspace(c)) {
//             col++;
//             continue;
//         }
//         if (isalpha(c) || c == '_') {
//             int startCol = col;
//             char ident[64];
//             int i = 0;
//             ident[i++] = c;
//             col++;
//             while ((c = getc(fin)) != EOF && (isalnum(c) || c == '_')) {
//                 ident[i++] = c;
//                 col++;
//             }
//             ident[i] = '\0';
//             if (c != EOF) {
//                 ungetc(c, fin);
//                 col--;
//             }
//             t.row = row;
//             t.col = startCol;
//             strcpy(t.lexeme, ident);
//             const char *keywords[] = {"integer", "real", "double precision", "character", "logical", "if", "else", "do", "while", "return"};
//             int isKeyword = 0;
//             for (int j = 0; j < sizeof(keywords) / sizeof(keywords[0]); j++) {
//                 if (strcmp(ident, keywords[j]) == 0) {
//                     isKeyword = 1;
//                     break;
//                 }
//             }
//             if (isKeyword)
//                 strcpy(t.type, "Keyword");
//             else
//                 strcpy(t.type, "Identifier");
//             return t;
//         }
//     }
//     t.row = -1;
//     return t;
// }

// int main() {
//     FILE *fin = fopen("input.f90", "r");
//     if (!fin) {
//         printf("Error opening file.\n");
//         return 1;
//     }

//     struct symbol symTable[MAX_SYMBOLS];
//     int symCount = 0;
//     int inDeclaration = 0;
//     char currentType[30] = "";

//     struct token t;
//     while ((t = getNextToken(fin)).row != -1) {
//         if (strcmp(t.type, "Keyword") == 0 && (strcmp(t.lexeme, "integer") == 0 || strcmp(t.lexeme, "real") == 0 || strcmp(t.lexeme, "double precision") == 0 || strcmp(t.lexeme, "character") == 0 || strcmp(t.lexeme, "logical") == 0)) {
//             inDeclaration = 1;
//             strcpy(currentType, t.lexeme);
//             continue;
//         }
//         if (inDeclaration) {
//             if (strcmp(t.type, "Identifier") == 0) {
//                 int exists = 0;
//                 for (int i = 0; i < symCount; i++) {
//                     if (strcmp(symTable[i].name, t.lexeme) == 0) {
//                         exists = 1;
//                         break;
//                     }
//                 }
//                 if (!exists && symCount < MAX_SYMBOLS) {
//                     symTable[symCount].index = symCount;
//                     strcpy(symTable[symCount].name, t.lexeme);
//                     strcpy(symTable[symCount].type, currentType);
//                     symCount++;
//                 }
//             }
//             if (strcmp(t.lexeme, "::") == 0 || strcmp(t.lexeme, ",") == 0) {
//                 continue;
//             }
//             if (strcmp(t.lexeme, "\n") == 0) {
//                 inDeclaration = 0;
//                 currentType[0] = '\0';
//             }
//         }
//     }

//     fclose(fin);

//     printf("\nSymbol Table:\n");
//     printf("Index\tName\tType\n");
//     printf("-----\t----\t----\n");
//     for (int i = 0; i < symCount; i++) {
//         printf("%d\t%s\t%s\n", symTable[i].index, symTable[i].name, symTable[i].type);
//     }
//     return 0;
// }

// perl

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

// #define MAX_TOKENS 1024
// #define MAX_SYMBOLS 256

// struct token {
//     char lexeme[64];
//     int row, col;
//     char type[30];
// };

// struct symbol {
//     int index;
//     char name[64];
//     char type[30];
// };

// int row = 1, col = 1;

// struct token getNextToken(FILE *fin) {
//     struct token t;
//     t.row = -1;
//     char c;
//     while ((c = getc(fin)) != EOF) {
//         if (c == '\n') {
//             row++;
//             col = 1;
//             continue;
//         }
//         if (isspace(c)) {
//             col++;
//             continue;
//         }
//         if (isalpha(c) || c == '$') {
//             int startCol = col;
//             char ident[64];
//             int i = 0;
//             ident[i++] = c;
//             col++;
//             while ((c = getc(fin)) != EOF && (isalnum(c) || c == '_')) {
//                 ident[i++] = c;
//                 col++;
//             }
//             ident[i] = '\0';
//             if (c != EOF) {
//                 ungetc(c, fin);
//                 col--;
//             }
//             t.row = row;
//             t.col = startCol;
//             strcpy(t.lexeme, ident);
//             const char *keywords[] = {"my", "our", "sub", "if", "else", "while", "for", "foreach", "return"};
//             int isKeyword = 0;
//             for (int j = 0; j < sizeof(keywords) / sizeof(keywords[0]); j++) {
//                 if (strcmp(ident, keywords[j]) == 0) {
//                     isKeyword = 1;
//                     break;
//                 }
//             }
//             if (isKeyword)
//                 strcpy(t.type, "Keyword");
//             else
//                 strcpy(t.type, "Identifier");
//             return t;
//         }
//     }
//     t.row = -1;
//     return t;
// }

// int main() {
//     FILE *fin = fopen("input.pl", "r");
//     if (!fin) {
//         printf("Error opening file.\n");
//         return 1;
//     }

//     struct symbol symTable[MAX_SYMBOLS];
//     int symCount = 0;
//     int inDeclaration = 0;
//     char currentType[30] = "";

//     struct token t;
//     while ((t = getNextToken(fin)).row != -1) {
//         if (strcmp(t.type, "Keyword") == 0 && strcmp(t.lexeme, "my") == 0) {
//             inDeclaration = 1;
//             continue;
//         }
//         if (inDeclaration) {
//             if (strcmp(t.type, "Identifier") == 0) {
//                 int exists = 0;
//                 for (int i = 0; i < symCount; i++) {
//                     if (strcmp(symTable[i].name, t.lexeme) == 0) {
//                         exists = 1;
//                         break;
//                     }
//                 }
//                 if (!exists && symCount < MAX_SYMBOLS) {
//                     symTable[symCount].index = symCount;
//                     strcpy(symTable[symCount].name, t.lexeme);
//                     strcpy(symTable[symCount].type, "Variable");
//                     symCount++;
//                 }
//             }
//             if (strcmp(t.lexeme, ";") == 0) {
//                 inDeclaration = 0;
//             }
//         }
//     }

//     fclose(fin);

//     printf("\nSymbol Table:\n");
//     printf("Index\tName\tType\n");
//     printf("-----\t----\t----\n");
//     for (int i = 0; i < symCount; i++) {
//         printf("%d\t%s\t%s\n", symTable[i].index, symTable[i].name, symTable[i].type);
//     }
//     return 0;
// }
