# almost all the pointer warnings are dumb
flags = -Wno-pointer-sign -Wno-incompatible-pointer-types


all: main.o tests.o parser.o
	cc -o bin $^

main.o: main.c
	cc -c main.c

tests.o: tests.c
	cc -c tests.c $(flags)

parser.o: parser.c
	cc -c parser.c $(flags) 

clean:
	rm -rf *.o bin
