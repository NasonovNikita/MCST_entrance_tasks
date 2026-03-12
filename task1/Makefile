CC = gcc
LDFLAGS = -lm
CFLAGS = -Wall -Wextra -Werror

# For CLion to configure project correctly
all: task1

debug: CFLAGS += -DDEBUG -g
debug: clean main.o
	$(CC) $(CFLAGS) main.o -o task1 $(LDFLAGS)

main.o: main.c max_threads.h
	$(CC) $(CFLAGS) -c $< -o $@

task1: main.o
	$(CC) $(CFLAGS) main.o -o task1 $(LDFLAGS)

clean:
	rm -f *.o task1

.PHONY: all debug clean