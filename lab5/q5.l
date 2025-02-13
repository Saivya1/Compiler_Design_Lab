%{
#include <stdio.h>
#include <stdlib.h>

int yywrap() { return 1; }
%}

%%
[0-9]+           { 
                    int num = atoi(yytext); 
                    printf("Hexadecimal: 0x%x\n",num); 
                 }

.                { }

%%

int main() {
    printf("enter a number: ");
    yylex();  
    return 0;
}
