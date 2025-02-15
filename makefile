

all: main.o tests.o parser.o
	cc -o bin $^

main.o: main.c
	cc -c main.c

tests.o: tests.c
	cc -c tests.c -Wno-pointer-sign

parser.o: parser.c
	cc -c parser.c

clean:
	rm -rf *.o bin
