//
// Created by nosokvkokose on 13.03.26.
//

#pragma once

#ifndef MY_FIFO_H
#define MY_FIFO_H

#include <unistd.h>

typedef struct {
    int fd;
    int mode;
} fifo_handler_t;

int open_fifo_read(fifo_handler_t *fifo, char* path);
int open_fifo_write(fifo_handler_t *fifo, char* path);
ssize_t read_from_fifo(fifo_handler_t *fifo, char* buffer, size_t size);
ssize_t write_to_fifo(fifo_handler_t *fifo, const char* message, size_t size);
// Free channel, path is not deleted
void free_fifo(fifo_handler_t *fifo);

#endif //MY_FIFO_H
