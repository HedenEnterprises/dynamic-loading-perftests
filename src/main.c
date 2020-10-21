/*
base64 /dev/urandom | head -c 100000000 > text.file
echo "found" >> text.file
*/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

/*
gcc -O0 -g3 main.c module.c -D TEST_STATIC -o static

gcc -fPIC -O0 -g3 main.c -D TEST_DYNAMIC -o dynamic -ldl
gcc -fPIC -O0 -g3 main.c -D TEST_DYNAMIC -o dynamic -shared
*/


#ifdef TEST_STATIC

int module_func(const char * file);

#endif


int main(int argc, char const *argv[])
{

#ifdef TEST_STATIC
    if (argc != 3) {
        printf("Command is: %s <test-count> <test-file> \n", argv[0]);
    }
#else
    if (argc != 5) {
        printf("Command is: %s <test-count> <test-file> <module> <1=RTLD_LAZY,2=RTLD_NOW>\n", argv[0]);
    }
#endif

    unsigned int test_count = atoi(argv[1]);
    const char * test_file = argv[2];

#ifdef TEST_DYNAMIC
    const char * module = argv[3];
    int dlopen_flags = atoi(argv[4]);

    switch (dlopen_flags) {
    case 1:
        dlopen_flags = RTLD_LAZY;
        break;
    case 2:
    default:
        dlopen_flags = RTLD_NOW;
        break;
    }

    void * handle = dlopen(module, dlopen_flags);
    int (* func)(const char *) = dlsym(handle, "module_func");
#else
    int (* func)(const char *) = module_func;
#endif

    int i = 0;

    for (i = 0; i < test_count; i++) {
        char * file = strdup(test_file);
        printf("%d,", func(file));
        free(file);
    }

    printf("%s\n", "");

    return 0;
}
