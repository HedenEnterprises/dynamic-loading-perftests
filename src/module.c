
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* base64 (we use to generate test-file) max line length is 76,
   so +1 for null, and +5 for 'found' */
#define BUFFER_SIZE 76 + 1 + 5


int module_func(char * file)
{
    int return_code = -1;
    char str[BUFFER_SIZE] = { 0 };
    char * pos = NULL;

    unsigned int line = 0;
    unsigned int col  = 0;

    FILE * fp = fopen(file, "r");

    if (fp == NULL) {
        return return_code;
    }

    while ((fgets(str, BUFFER_SIZE, fp)) != NULL) {
        line += 1;

        pos = strstr(str, "found");

        if (pos != NULL) {
            col = (pos - str);
        }
    }

    fclose(fp);
    return line * 77 + col;
}
