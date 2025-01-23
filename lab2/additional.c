#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_DATA_TYPES 10

const char *data_types[MAX_DATA_TYPES] = {
    "void", "int", "char", "float", "double", "long", "signed", "struct", "short", "unsigned"
};

int is_data_type(const char *word) {
    for (int i = 0; i < MAX_DATA_TYPES; i++) {
        if (strcmp(word, data_types[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int count_arguments(const char *signature) {
    int count = 0;
    int inside_parens = 0;
    
    for (int i = 0; signature[i] != '\0'; i++) {
        if (signature[i] == '(') {
            inside_parens = 1;
        } else if (signature[i] == ')') {
            inside_parens = 0;
        } else if (inside_parens && signature[i] == ',') {
            count++;
        }
    }
    
    return count + (inside_parens ? 1 : 0);
}

void process_function(char *line) {
    char return_type[MAX_LINE_LENGTH];
    char func_name[MAX_LINE_LENGTH];
    char signature[MAX_LINE_LENGTH];
    int num_args = 0;

    if (sscanf(line, "%s %s", return_type, func_name) == 2 && is_data_type(return_type)) {
        char *parens_start = strchr(line, '(');
        if (parens_start != NULL) {
            char *parens_end = strchr(parens_start, ')');
            if (parens_end != NULL) {
                strncpy(signature, parens_start, parens_end - parens_start + 1);
                signature[parens_end - parens_start + 1] = '\0';
                
                num_args = count_arguments(signature);
                
                printf("Function: %s\n", func_name);
                printf("Return Type: %s\n", return_type);
                printf("Number of Arguments: %d\n\n", num_args);
            }
        }
    }
}

int main() {
    FILE *fa;
    char line[MAX_LINE_LENGTH];

    fa = fopen("q1_code.c", "r");
    if (fa == NULL) {
        printf("Cannot open file\n");
        exit(0);
    }

    while (fgets(line, sizeof(line), fa)) {
        if (line[0] == '\0' || line[0] == '/' || line[0] == '\n') continue;

        process_function(line);
    }

    fclose(fa);
    return 0;
}
