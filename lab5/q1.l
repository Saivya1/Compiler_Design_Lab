%{
#include <stdio.h>
#include <ctype.h>

int vowels = 0;
int consonants = 0;
int yywrap() { return 1; }
%}

%%
[aAeEiIoOuU]      { vowels++; }
[bcdfghjklnmpqstvwxyzBCDFGJKLNMPQSTVWXYZ] { consonants++; }
[ \t\n]
%%

int main() {
    printf("Enter a string:\n");
    yylex();  
    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    return 0;
}
