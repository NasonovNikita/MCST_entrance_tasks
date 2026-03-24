//
// Created by nosokvkokose on 20.03.26.
//

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#define PARENT_COPY_FILE_NAME "parent_copy"
#define CHILD_COPY_FILE_NAME "child_copy"
#define BUFFER_SIZE 1024

void copy_file(FILE* original, FILE* copy) {
    if (original == NULL || copy == NULL) {
        perror("fopen");
        return;
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), original) != NULL) {
        fputs(buffer, copy);
    }
}

int main(const int argc, char* argv[]) {\
    if (argc != 2) {
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    const pid_t pid = fork();

    const char* file_name = argv[1];
    FILE* input_file = fopen(file_name, "r");
    if (input_file == NULL) {
        perror("fopen");
        return 1;
    }


    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {  // Child process
        FILE* child_copy = fopen(CHILD_COPY_FILE_NAME, "w");
        if (child_copy == NULL) {
            perror("fopen");
            return 1;
        }

        copy_file(input_file, child_copy);
        fclose(child_copy);
    } else {  // Parent process
        FILE* parent_copy = fopen(PARENT_COPY_FILE_NAME, "w");
        if (parent_copy == NULL) {
            perror("fopen");
            return 1;
        }

        copy_file(input_file, parent_copy);
        fclose(parent_copy);
    }

    fclose(input_file);

    return 0;
}
