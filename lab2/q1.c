#include <stdio.h>
#include <stdlib.h>
int main()
{
FILE *fa, *fb;
int ca, cb;
fa = fopen("q1_code.c", "r");
if (fa == NULL){
printf("Cannot open file \n");
exit(0); 
}
fb = fopen("q1_code_out.c", "w");
ca = getc(fa);
while (ca != EOF)
{
    if(ca==' ')
    {
        putc(' ',fb);
        while(ca==' ')
            ca = getc(fa);
    }
    if (ca=='/')
    {
        cb = getc(fa);
        if (cb == '/')
        {
            while(ca != '\n')
                ca = getc(fa);
        }
    
        else if (cb == '*'){
            do
            {
                while(ca != '*')
                    ca = getc(fa);
                    ca = getc(fa);
            } while (ca != '/');
        }
        else
        {
            putc(ca,fb);
            putc(cb,fb);
        }
    }
    else
    { 
        putc(ca,fb);
    }
    ca = getc(fa);
}
fclose(fa);
fclose(fb);
return 0;
}
