
CFLAGS=-O0 -g3
MODCFLAGS=-fPIC -shared
DLLIB=-ldl

DEFSTATIC=-D TEST_STATIC
DEFDYNAMIC=-D TEST_DYNAMIC

all: static dynamic module.so

static: main.c module.c
	gcc $(CFLAGS) main.c module.c $(DEFSTATIC) -o $@

dynamic: main.c
	gcc $(CFLAGS) main.c $(DEFDYNAMIC) -o $@ $(DLLIB)

module.so: module.c
	gcc $(CFLAGS) module.c $(DEFDYNAMIC) -o $@ $(MODCFLAGS)

generate-test-file:
	base64 /dev/urandom | head -c 100000000 > test-file
	echo "found" >> test-file

run-static:
	./static 10 test-file

run-dynamic:
	./dynamic 10 test-file module.so 1
