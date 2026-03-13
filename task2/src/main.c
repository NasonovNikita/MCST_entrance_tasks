//
// Created by nosokvkokose on 12.03.26.
//

#include <signal.h>
#include <stdio.h>

#include "messager.h"

messager_t messager;

void sigint_handler(int sig) {
    (void)sig;  // unused

    cleanup_messager(&messager);
}

int main(const int argc, char* argv[]) {
    signal(SIGINT, sigint_handler);  // To free fifo on exit

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fifo file>\n", argv[0]);
        return 1;
    }
    char* path = argv[1];
#ifdef DEBUG
    printf("FIFO path: %s\n", path);
#endif

    if (init_messager(&messager, path) == -1) {
        fprintf(stderr, "Failed to init messager\n");
        return 1;
    }

    while (true) {
        handle_messager(&messager);  // SIGINT or error exit only
    }

    return 0;
}
