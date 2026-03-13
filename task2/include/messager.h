//
// Created by nosokvkokose on 13.03.26.
//

#pragma once

#ifndef MESSAGER_H
#define MESSAGER_H

#include "my_fifo.h"

enum messager_mode {
    READ,
    WRITE
};

typedef struct {
    enum messager_mode mode;
    char* fifo_path;
    fifo_handler_t fifo;
} messager_t;

int init_messager(messager_t* messager, char* fifo_path);
void handle_messager(messager_t* messager);

void cleanup_messager(messager_t* messager);

#endif //MESSAGER_H
