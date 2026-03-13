//
// Created by nosokvkokose on 13.03.26.
//

#pragma once

#ifndef MESSAGER_H
#define MESSAGER_H

#include "my_fifo.h"

enum massager_mode {
    READ,
    WRITE
};

typedef struct {
    enum massager_mode mode;
    char* fifo_path;
    fifo_handler_t fifo;
} massager_t;

int init_massager(massager_t* massager, char* fifo_path);
void handle_massager(massager_t* massager);

#endif //MESSAGER_H
