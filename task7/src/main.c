//
// Created by nosokvkokose on 20.03.26.
//

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PARENT_COPY_FILE_NAME "parent_copy"
#define CHILD_COPY_FILE_NAME "child_copy"
#define BUFFER_SIZE 1024

void copy_file(FILE* original, FILE* copy) {
    rewind(original);
    if (original == NULL || copy == NULL) {
        perror("fopen");
        return;
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), original) != NULL) {
        fputs(buffer, copy);
    }
}

FILE* open_file(const char* file_name, const char* mode) {
    FILE* file = fopen(file_name, mode);
    if (file == NULL) {
        perror("fopen");
        exit(1);  // Terminal issue in this task, so exit
    }

    return file;
}

int main(const int argc, char* argv[]) {\
    if (argc != 2) {
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    const pid_t pid = fork();

    const char* file_name = argv[1];
    FILE* input_file = open_file(file_name, "r");


    if (pid == -1) {
        perror("fork");
        return 1;
    }

    FILE* output_file;

    if (pid == 0) {  // Child process
        output_file = open_file(CHILD_COPY_FILE_NAME, "w");
        // Print Parent: [contents]
        printf("Child: \n");
    } else {  // Parent process
        output_file = open_file(PARENT_COPY_FILE_NAME, "w");
        printf("Parent: \n");
    }
    copy_file(input_file, output_file);
    copy_file(input_file, stdout);
    printf("\n");  // Add newline after printing contents

    fclose(input_file);
    fclose(output_file);

    return 0;
}
