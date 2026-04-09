//
// Created by nosokvkokose on 09.04.26.
//

#ifndef MATRIX_H
#define MATRIX_H

#pragma once

#include <stddef.h>

typedef struct {
    size_t sizeX;
    size_t sizeY;
    int **matrix;
} matrix_t;

// Create matrix with sizeX columns and sizeY rows filled with zeros
matrix_t create_matrix(size_t sizeX, size_t sizeY);

void free_matrix(const matrix_t *matrix);

matrix_t copy_matrix(const matrix_t *matrix_to_copy);

#endif //MATRIX_H
