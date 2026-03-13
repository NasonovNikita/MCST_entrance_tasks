//
// Created by nosokvkokose on 13.03.26.
//

#include "messager.h"

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "my_fifo.h"

#define STATE_SWITCH_TIMEOUT 2
#define BUFFER_SIZE 1024


void switch_mode(messager_t* messager) {
    free_fifo(&messager->fifo);

    if (messager->mode == READ) {
        messager->mode = WRITE;
        open_fifo_write(&messager->fifo, messager->fifo_path);
    } else {
        messager->mode = READ;

        // Loop to wait for reader
        time_t start = time(NULL);
        while (open_fifo_read(&messager->fifo, messager->fifo_path) == -1) {
            if (time(NULL) - start > STATE_SWITCH_TIMEOUT) {
                fprintf(stderr, "Timeout\n");
                exit(1);  // Unrecoverable error
            }
        }
    }

#ifdef DEBUG
    printf("Switched to %s mode\n", messager->mode == READ ? "READ" : "WRITE");
#endif
}

int init_messager(messager_t* messager, char* fifo_path) {
#ifdef DEBUG
    printf("init_messager called with path=%s\n", fifo_path);
#endif
    fifo_handler_t fifo;
    messager->fifo_path = fifo_path;

    // Try write
    messager->mode = WRITE;
    int fd = open_fifo_write(&fifo, fifo_path);
    if (fd != -1) {
        messager->fifo = fifo;
#ifdef DEBUG
        printf("Messager initialized in WRITER mode\n");
#endif
        return fd;
    }

    if (errno == ENXIO) {
#ifdef DEBUG
        printf("No reader, attempting to become reader\n");
#endif
        // Try read instead
        fd = open_fifo_read(&fifo, fifo_path);
        messager->mode = READ;
        if (fd == -1) {
            perror("Fifo doesn't exist or has both reader and writer\n");
            return -1;
        }
        messager->fifo = fifo;
#ifdef DEBUG
        printf("Messager initialized in READER mode\n");
#endif
        return fd;
    }

    return -1;
}

void handle_messager(messager_t *messager) {
    if (messager->mode == READ) {
        char buffer[BUFFER_SIZE];
        ssize_t bytes;
        while ((bytes = read_from_fifo(&messager->fifo, buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes] = '\0';
            printf("%s", buffer);
        }
#ifdef DEBUG
        printf("Exiting read mode\n");
#endif
    } else {  // WRITE
        char *line = NULL;
        size_t len = 0;
        ssize_t nread;
        if ((nread = getline(&line, &len, stdin)) != -1) {
#ifdef DEBUG
            printf("Read %zd bytes: %s", nread, line);
#endif
            write_to_fifo(&messager->fifo, line, nread);
        }
#ifdef DEBUG
        printf("Exiting write mode\n");
#endif
        free(line);
    }

    switch_mode(messager);
}

void cleanup_messager(messager_t *messager) {
#ifdef DEBUG
    printf("Cleaning up messager\n");
#endif
    free_fifo(&messager->fifo);
}
