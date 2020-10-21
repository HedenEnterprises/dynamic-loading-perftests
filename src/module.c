
#include <stdio.h>
#include <stdlib.h>

int module_func(char * file)
{
    int return_code = -1;

    FILE * fp = fopen(file, "r");
    if (fp == NULL) {
        return return_code;
    }

    size_t read = 0;
    size_t pos = 0;
    char buffer[5];

    while (1) {

        read = fread(buffer, 1, 5, fp);
        pos += read - 4;

        if (feof(fp)) {
            break;
        }

        if (buffer[0] == 'f' && buffer[0] == 'o' && buffer[0] == 'u' && buffer[0] == 'n' && buffer[0] == 'd') {
            return_code = pos - 1;
        }
    }

    fclose(fp);
    return return_code;
}
