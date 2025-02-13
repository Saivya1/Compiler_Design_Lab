%{
#include <stdio.h>
#include <ctype.h>  

int yywrap() {
    return 1; 
}

%}

%%
"//".*            {printf("%s", yytext);  }
"/*"[^*]*"*/"     {printf("%s", yytext);  }
[A-Z]              { printf("%c", tolower(yytext[0])); }  
.                  { printf("%s", yytext); }
%%

int main() {
    
    FILE *input = fopen("input.c", "r");
  
    yyin = input;
    
    yylex();

    fclose(input);

    return 0;
}
