//
// Created by nosokvkokose on 12.03.26.
//

#include <stdio.h>


int main(const int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fifo file>\n", argv[0]);
        return 1;
    }
    char* path = argv[1];


    return 0;
}
