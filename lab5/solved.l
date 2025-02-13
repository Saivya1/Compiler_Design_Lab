%{
#include <stdio.h>
int yywrap() { return 1; }  
%}

%%
[a-zA-Z_][a-zA-Z0-9_]*  { printf("Identifier: %s\n", yytext); }
%%

int main() {
    printf("Enter a valid C statement:\n");
    yylex();  
    return 0;
    yywrap();
}
