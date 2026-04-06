//
// Created by nosokvkokose on 06.04.26.
//

#include "sequence_scan.h"

#include <limits.h>
#include <stddef.h>
#include <stdio.h>

inline bool greater_seq(const index_tuple first, const index_tuple second) {
    return first.second - first.first > second.second - second.first;  // lol
}

index_tuple get_longest_rising_seq_indices(const int *arr, const size_t size) {
    index_tuple result_seq = {0};
    size_t first_index = 0;
    int last = INT_MIN;  // Start at min to always get bigger val first
    for (size_t i = 0; i < size; i++) {
        if (arr[i] <= last) {
            const index_tuple found_seq = {first_index, i};  // Second is excluding
            if (greater_seq(found_seq, result_seq)) {
                result_seq = found_seq;
            }

            first_index = i;  // Search from here
        }
        last = arr[i];
    }

#ifdef DEBUG
    printf("last found: %d, last in arr: %d\n", last, arr[size - 1]);
    printf("first index: %ld, size - 1 = %ld\n", first_index, size);
#endif

    if (first_index != size - 1) {  // If last didn't fail, first_index isn't updated
        const index_tuple found_seq = {first_index, size};  // Second is excluding
        if (greater_seq(found_seq, result_seq)) {
            result_seq = found_seq;
        }
    }

    return result_seq;
}
