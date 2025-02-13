%{
#include <stdio.h>

int pos_int = 0;
int neg_int = 0;
int pos_fl = 0;
int neg_fl = 0;
int yywrap() { return 1; }
%}

%%
[0-9]+           { pos_int++; }
-[0-9]+          { neg_int++; }
[0-9]+\.[0-9]+    { pos_fl++; }
-[0-9]+\.[0-9]+   { neg_fl++; }
%%

int main() {
    yylex();
    printf("positive integers : %d\n", pos_int);
    printf("negative integers : %d\n", neg_int);
    printf("positive floating point numbers : %d\n", pos_fl);
    printf("negative floating point numbers : %d\n", neg_fl);
    return 0;
}
