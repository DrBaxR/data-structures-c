LIBS_DIR=src/lib
LIBS=$(LIBS_DIR)/util.c $(LIBS_DIR)/list.c $(LIBS_DIR)/stack.c $(LIBS_DIR)/btree.c

all: main

main: libds.so
	gcc -o bin/main src/main.c -Lbin -lds

libds.so: bin
	gcc -shared -o bin/libds.so -fPIC $(LIBS)

bin:
	mkdir bin

run: main
	LD_LIBRARY_PATH="./bin:LD_LIBRARY_PATH" bin/main

clean:
	rm -r bin
