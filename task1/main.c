//
// Created by nosokvkokose on 10.03.26.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int elem_to_sort_count;
    int elem_start;  // index of first element to sort
    int* arr;
} pthrData_t;  // sort arr[elem_start:elem_start+elem_to_sort_count]

// TODO: implement
void* thread_sort(void* data);

// TODO: implement
// Sorts arr using num_threads threads
void launch_thread_sorts(int *arr, int size, int num_threads);

// Saves array from stdin to arr, returns size of array
int scan_arr(int* arr) {
    int size = 0;
    int num;
    while (scanf("%d", &num) == 1) {
        size++;
        realloc(arr, size * sizeof(int));
        arr[size - 1] = num;
    }

    return size;
}

int main(const int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Number of threads required, example: ./task1 10\n");
        return 1;
    }
    if (argc > 2) {
        fprintf(stderr,
            "Warning: Too many arguments, ignoring all except first\n");
    }

    const int thread_count = atoi(argv[1]);
    // Check that argv[0] is positive int
    if (thread_count <= 0) {
        fprintf(stderr, "Number of threads must be a positive integer\n");
        return 1;
    }

    int* arr;
    int size = scan_arr(arr);

    // TODO: gen thread data

    // TODO: launch

    // TODO: print

    free(arr);

    return 0;
}
