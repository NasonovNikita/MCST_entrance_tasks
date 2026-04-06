//
// Created by nosokvkokose on 20.03.26.
//

#include <stdlib.h>

#include "tools.h"
#include "sequence_scan.h"

int main() {
    int* arr;
    const size_t size = scan_arr(&arr);

    const index_tuple longest_seq = get_longest_rising_seq_indices(arr, size);
    print_arr(&arr[longest_seq.first], longest_seq.second - longest_seq.first);

    free(arr);

    return 0;
}
