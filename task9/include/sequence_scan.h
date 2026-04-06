//
// Created by nosokvkokose on 06.04.26.
//

#ifndef SEQUENCE_SCAN_H
#define SEQUENCE_SCAN_H
#include <stddef.h>

typedef struct {
    size_t first;
    size_t second;
} index_tuple;

bool greater_seq(index_tuple first, index_tuple second);

index_tuple get_longest_rising_seq_indices(const int *arr, size_t size);

#endif //SEQUENCE_SCAN_H
