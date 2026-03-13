//
// Created by nosokvkokose on 12.03.26.
//

#include <stdio.h>

#include "messager.h"


int main(const int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fifo file>\n", argv[0]);
        return 1;
    }
    char* path = argv[1];

    massager_t massager;
    init_massager(&massager, path);


    return 0;
}
