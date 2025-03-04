# almost all the pointer warnings are dumb
flags = -Wno-pointer-sign -Wno-incompatible-pointer-types


all: main.o tests.o parser.o search.o objwrite.o symboltable.o
	cc -o bin $^

main.o: main.c
	cc -c main.c $(flags)

tests.o: tests.c
	cc -c tests.c $(flags)

parser.o: parser.c
	cc -c parser.c $(flags) 

search.o: search.c
	cc -c search.c

objwrite.o: objwrite.c
	cc -c objwrite.c $(flags)

symboltable.o: symboltable.c
	cc -c symboltable.c $(flags)

clean:
	rm -rf *.o bin
