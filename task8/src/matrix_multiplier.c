//
// Created by nosokvkokose on 08.04.26.
//

#include "matrix_multiplier.h"


void matrix_multiplier_init(matrix_multiplier *multiplier, matrix_t *matrix1,
                            matrix_t *matrix2) {
    multiplier->line = 0;
    multiplier->column = 0;
    multiplier->index = 0;

    multiplier->matrix1 = copy_matrix(matrix1);
    multiplier->matrix2 = copy_matrix(matrix2);
    multiplier->result = create_matrix(matrix2->sizeX, matrix1->sizeY);
}

void free_matrix_multiplier(const matrix_multiplier *multiplier) {
    free_matrix(&multiplier->matrix1);
    free_matrix(&multiplier->matrix2);
    free_matrix(&multiplier->result);
}

bool matrix_multiplier_step(matrix_multiplier *multiplier) {
    if (multiplier->line == multiplier->matrix1.sizeY) {  // Iterated all lines
        return false;
    }

    multiplier->result.matrix[multiplier->line][multiplier->column] +=
        multiplier->matrix1.matrix[multiplier->line][multiplier->index] *
        multiplier->matrix2.matrix[multiplier->index][multiplier->column];

    multiplier->index++;

    // Update indexes
    if (multiplier->index == multiplier->matrix1.sizeX) {
        // Update column
        multiplier->index = 0;
        multiplier->column++;

        // Or even line
        if (multiplier->column == multiplier->matrix2.sizeX) {
            multiplier->column = 0;
            multiplier->line++;
        }
    }

    return true;
}

// Returns a copy of result of multiplication
matrix_t matrix_multiplier_get_result(const matrix_multiplier *multiplier) {
    return copy_matrix(&multiplier->result);
}
