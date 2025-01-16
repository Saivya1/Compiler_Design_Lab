#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fa, *fb;
    int ca, cb;

   
    fa = fopen("q1_code.c", "r");
    if (fa == NULL) {
        printf("Cannot open input file\n");
        exit(0);
    }

    
    fb = fopen("q2_code_out.c", "w");
    

    ca = getc(fa); 

    while (ca != EOF) {
        if (ca == '#') { 
            
            while (ca != '\n' && ca != EOF) {
                ca = getc(fa);
            }
        } else {
            
            putc(ca, fb);
            ca = getc(fa); 
        }
    }

    fclose(fa); 
    fclose(fb); 

    

    return 0;
}
