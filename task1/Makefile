main.o: main.c
	gcc -c main.c -o main.o

debug:
	gcc -DDEBUG main.c -o task1

task1: main.o
	gcc main.o -o task1

clean:
	rm -f *.o task1
