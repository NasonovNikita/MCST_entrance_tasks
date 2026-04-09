//
// Created by nosokvkokose on 20.03.26.
//

#define MATRIX_SIZE 100

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include "matrix_multiplier.h"

enum signal_method {
    SIGNAL,
    SIGACTION
};

matrix_multiplier multiplier;
enum signal_method signal_method;

void print_multiplier_position() {
    printf("\n%ld %ld\n%ld %ld\n%ld %ld\n", multiplier.line, multiplier.index,
        multiplier.index, multiplier.column, multiplier.line, multiplier.column);
}

void handle_signal(int sig) {
    (void) sig;  // Unused

    print_multiplier_position();

    if (signal_method == SIGNAL) {
        signal(SIGINT, SIG_DFL);
    } else if (signal_method == SIGACTION) {
        struct sigaction sa_default;
        sa_default.sa_handler = SIG_DFL;
        sigemptyset(&sa_default.sa_mask);
        sa_default.sa_flags = 0;

        sigaction(SIGINT, &sa_default, NULL);
    }
}


int main(const int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <signal method: --signal or --sigaction>\n", argv[0]);
        return 1;
    }
    // Find out with method is used
    if (strcmp(argv[1], "--signal") == 0) {
        signal(SIGINT, handle_signal);
    } else if (strcmp(argv[1], "--sigaction") == 0) {
        struct sigaction sa;
        sa.sa_handler = handle_signal;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;

        sigaction(SIGINT, &sa, NULL);
    }

    matrix_t matrix1 = create_matrix(MATRIX_SIZE, MATRIX_SIZE);
    matrix_t matrix2 = create_matrix(MATRIX_SIZE, MATRIX_SIZE);
    matrix_multiplier_init(&multiplier, &matrix1, &matrix2);

    while (matrix_multiplier_step(&multiplier)) {
        sleep(0.5);
    }

    return 0;
}
