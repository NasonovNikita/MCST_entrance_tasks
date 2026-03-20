//
// Created by nosokvkokose on 20.03.26.
//

#ifndef DONT_USE_GNU_ERROR_HANDLING
#define _GNU_SOURCE  // To get same output as in task example
#endif

#include <errno.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE *file = fopen("mega_aboba.txt", "r");

    if (file == NULL) {
        perror("Can't open file");

#ifndef DONT_USE_GNU_ERROR_HANDLING
        fprintf(stderr, "Errno = %s\n", strerrorname_np(errno));
#else
        fprintf(stderr, "Errno = %d\n", errno);
#endif

        // This error catching method is not supported
        // extern int sys_nerr;
        // extern char *sys_errlist[];
        // if (errno < sys_nerr)
        //     printf("%s\n", sys_errlist[errno]);

    } else {
        printf("How did we get here?\n");
        fclose(file);
    }

    return 0;
}
