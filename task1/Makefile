# For CLion to configure project correctly
all: task1

main.o: main.c
	gcc -c main.c -o main.o

debug:
	gcc -DDEBUG main.c -o task1 -lm

task1: main.o
	gcc main.o -o task1 -lm

clean:
	rm -f *.o task1
