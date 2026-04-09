//
// Created by nosokvkokose on 08.04.26.
//

#ifndef MATRIX_MULTIPLIER_H
#define MATRIX_MULTIPLIER_H

#pragma once

#include "matrix.h"

typedef struct {
    matrix_t matrix1;
    matrix_t matrix2;
    matrix_t result;

    size_t line;
    size_t column;
    size_t index;
} matrix_multiplier;  // Stores matrix multiplication data step by step

void matrix_multiplier_init(matrix_multiplier *multiplier,
    matrix_t *matrix1, matrix_t *matrix2);

void free_matrix_multiplier(const matrix_multiplier *multiplier);

// Returns true if the step was successful
bool matrix_multiplier_step(matrix_multiplier *multiplier);

// Returns a copy of the result matrix
matrix_t matrix_multiplier_get_result(const matrix_multiplier *multiplier);

#endif //MATRIX_MULTIPLIER_H
