%{
#include <stdio.h>
#include <ctype.h>

int w = 0;
int c = 0;
int blank = 0;
int line = 0;
int yywrap() { return 1; }
%}

%%
\n               { line++; }
[ \t]            { blank++; }
[a-zA-Z0-9]+     { w++; c += yyleng; }
.                { c++; }
%%

int main() {
    yylex();
    printf("words: %d\n", w);
    printf("characters: %d\n", c);
    printf("blanks: %d\n", blank);
    printf("lines: %d\n", line);
    return 0;
}
