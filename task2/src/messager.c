//
// Created by nosokvkokose on 13.03.26.
//

#include "messager.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "my_fifo.h"

#define STATE_SWITCH_TIMEOUT 2
#define BUFFER_SIZE 1024

void switch_mode(massager_t* massager) {
    free_fifo(&massager->fifo);

    if (massager->mode == READ) {
        massager->mode = WRITE;
        open_fifo_write(&massager->fifo, massager->fifo_path);
    } else {
        massager->mode = READ;

        // Loop to wait for reader
        time_t start = time(NULL);
        while (open_fifo_read(&massager->fifo, massager->fifo_path) == -1) {
            if (time(NULL) - start > STATE_SWITCH_TIMEOUT) {
                perror("Timeout");
                exit(1);  // Unrecoverable error
            }
        }
    }
}

int init_massager(massager_t* massager, char* fifo_path) {
    fifo_handler_t fifo;
    massager->fifo_path = fifo_path;

    // Try write
    int fd = open_fifo_write(&fifo, fifo_path);
    massager->mode = WRITE;
    if (fd == -1) {
        // Try read instead
        fd = open_fifo_read(&fifo, fifo_path);
        massager->mode = READ;
        if (fd == -1) {
            perror("Fifo doesn't exist or has both reader and writer");
            return -1;
        }
    }
    massager->fifo = fifo;

    return 0;
}

void handle_massager(massager_t *massager) {
    if (massager->mode == READ) {
        char buffer[BUFFER_SIZE];
        ssize_t bytes;
        while ((bytes = read_from_fifo(&massager->fifo, buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes] = '\0';
            printf("%s", buffer);
        }
    } else {  // WRITE
        char *line = NULL;
        size_t len = 0;
        ssize_t nread;
        while ((nread = getline(&line, &len, stdin)) != -1) {
            write_to_fifo(&massager->fifo, line, nread);
        }
        free(line);
    }

    switch_mode(massager);
}
