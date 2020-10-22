
CFLAGS=-O0 -g3
MODCFLAGS=-fPIC -shared
DLLIB=-ldl

DEFSTATIC=-D TEST_STATIC
DEFDYNAMIC=-D TEST_DYNAMIC

TESTSCOUNT=50000

all: static dynamic module.so

static: main.c module.c
	gcc $(CFLAGS) main.c module.c $(DEFSTATIC) -o $@

dynamic: main.c
	gcc $(CFLAGS) main.c $(DEFDYNAMIC) -o $@ $(DLLIB)

module.so: module.c
	gcc $(CFLAGS) module.c $(DEFDYNAMIC) -o $@ $(MODCFLAGS)

generate-test-file:
	base64 /dev/urandom | head -c 10000 > test-file
	echo "found" >> test-file

run-static: generate-test-file static
	./static $(TESTSCOUNT) test-file

run-dynamic: run-dynamic-lazy

run-dynamic-lazy: generate-test-file dynamic module.so
	./dynamic $(TESTSCOUNT) test-file ./module.so 1

run-dynamic-now: generate-test-file dynamic module.so
	./dynamic $(TESTSCOUNT) test-file ./module.so 2
