//
// Created by nosokvkokose on 09.04.26.
//

#include <stdlib.h>
#include "matrix.h"

matrix_t create_matrix(const size_t sizeX, const size_t sizeY)  {
    matrix_t result;
    result.sizeX = sizeX;
    result.sizeY = sizeY;

    int **matrix = malloc(sizeY * sizeof(int*));
    for (size_t i = 0; i < sizeY; i++) {
        matrix[i] = malloc(sizeX * sizeof(int));
        for (size_t j = 0; j < sizeX; j++) {
            matrix[i][j] = 0;
        }
    }

    result.matrix = matrix;

    return result;
}

void free_matrix(const matrix_t *matrix)  {
    for (size_t i = 0; i < matrix->sizeY; i++) {
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
}


matrix_t copy_matrix(const matrix_t *matrix_to_copy) {
    const size_t sizeX = matrix_to_copy->sizeX;
    const size_t sizeY = matrix_to_copy->sizeY;
    const matrix_t result = create_matrix(sizeX, sizeY);

    for (size_t i = 0; i < sizeY; i++) {
        for (size_t j = 0; j < sizeX; j++) {
            result.matrix[i][j] = matrix_to_copy->matrix[i][j];
        }
    }

    return result;
}

