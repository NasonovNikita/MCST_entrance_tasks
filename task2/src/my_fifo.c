//
// Created by nosokvkokose on 13.03.26.
//

#include "my_fifo.h"

#include <errno.h>
#include <fcntl.h>
#include <sys/file.h>
#include <asm-generic/errno-base.h>

int open_fifo_read(fifo_handler_t *fifo, char *path) {
    const int fd = open(path, O_RDONLY);
    if (fd == -1) {
        return -1;
    }
    fifo->fd = fd;
    fifo->mode = O_RDONLY;
    return fd;
}

int open_fifo_write(fifo_handler_t *fifo, char *path) {
    const int fd = open(path, O_WRONLY | O_NONBLOCK);
    if (fd == -1) {
        return -1;
    }

    if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
        // Prevent second writer
        close(fd);
        errno = EAGAIN;
        return -1;
    }

    fifo->fd = fd;
    fifo->mode = O_WRONLY;
    return fd;
}

ssize_t read_from_fifo(fifo_handler_t *fifo, char *buffer, size_t size) {
    if (fifo->mode != O_RDONLY) {
        return -1;
    }
    return read(fifo->fd, buffer, size);
}

ssize_t write_to_fifo(fifo_handler_t *fifo, const char *message, size_t size) {
    if (fifo->mode != O_WRONLY) {
        return -1;
    }
    return write(fifo->fd, message, size);
}

void free_fifo(fifo_handler_t *fifo) {
    close(fifo->fd);
    fifo->mode = -1;
}
