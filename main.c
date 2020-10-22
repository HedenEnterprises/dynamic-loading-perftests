
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>


#ifdef TEST_STATIC

int module_func(char * file);

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

    if (handle == NULL) {
        printf("Error opening module: %s\n", module);
        return 1;
    }
#endif

    unsigned int i = 0;
    unsigned int r = 0;

    for (i = 0; i < test_count; i++) {

#ifdef TEST_DYNAMIC
        int (* func)(char *) = dlsym(handle, "module_func");
#else
        int (* func)(char *) = module_func;
#endif

        if (func == NULL) {
            printf("%s\n", "Error finding module_func()");
            return 2;
        }

        r += func((char *)test_file);
    }

    printf("%d\n", r);

    return 0;
}
