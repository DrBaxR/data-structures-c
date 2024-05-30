all: main

main: libds.so
	gcc -o bin/main src/main.c -Lbin -lds

libds.so: bin
	gcc -shared -o bin/libds.so -fPIC src/lib/ds.c

bin:
	mkdir bin

run: main
	LD_LIBRARY_PATH="./bin:LD_LIBRARY_PATH" bin/main

clean:
	rm -r bin
