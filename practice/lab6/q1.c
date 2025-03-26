/*
E --> TEprime
E' --> +TE' / 𝜖
T --> FT'
T' --> *FT' / 𝜖
F --> (E) / i
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int curr = 0;
char str[99];

void E();
void Eprime();
void T();
void Tprime();
void F();

void invalid()
{
    printf("-----------------ERROR!----------------\n");
    exit(0);
}

void valid()
{
    printf("----------------SUCCESS!---------------\n");
    exit(0);
}

void E()
{
    T();
    Eprime();
}

void Eprime()
{
    if (str[curr] == '+')
    {
        curr++;
        T();
        Eprime();
    }
    else
    {
    }
}

void T()
{
    F();
    Tprime();
}

void Tprime()
{
    if (str[curr] == '*')
    {
        curr++;
        F();
        Tprime();
    }
    else
    {
    }
}

void F()
{
    if (str[curr] == '(')
    {
        curr++;
        E();
        if (str[curr] == ')')
        {
            curr++;
            return;
        }
        else
        {
            invalid();
        }
    }
    else if (str[curr] == 'i')
    {
        curr++;
        return;
    }
    else
    {
        invalid();
    }
}

int main()
{
    printf("Enter a string : ");
    scanf("%s", str);
    E();
    if (str[curr] == '$')
    {
        valid();
    }
    else
    {
        printf("%c", str[curr]);
        invalid();
    }
}