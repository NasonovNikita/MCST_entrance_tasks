CC = gcc
LDFLAGS = -lm
CFLAGS = -Wall -Wextra -Werror
TARGET = task1

# For CLion to configure project correctly
all: task1

debug: CFLAGS += -DDEBUG -g
debug: clean $(TARGET)

%.o: %.c max_threads.h
	$(CC) $(CFLAGS) -c $< -o $@


$(TARGET): main.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@
-include *.d

clean:
	rm -f *.o $(TARGET)

.PHONY: all debug clean
