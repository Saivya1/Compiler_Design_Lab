%{
#include <stdio.h>

int scanf_count = 0;
int printf_count = 0;

int yywrap() {
    return 1; 
}
%}

%%
scanf              { printf("READ "); scanf_count++; }
printf             { printf("WRITE "); printf_count++; }
.                  { printf("%s", yytext); }
%%

int main() {
    
    FILE *input = fopen("input.c", "r");
  
    yyin = input;
    
    
    yylex();

    fclose(input);

 
    printf("\nnumber of scanf: %d\n", scanf_count);
    printf("number of printf: %d\n", printf_count);

    return 0;
}