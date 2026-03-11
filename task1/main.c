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
int scan_arr(int** arr_ptr) {
    int capacity = 1;
    int count = 0;
    *arr_ptr = malloc(capacity * sizeof(int));

    int num;
    while (scanf("%d", &num) == 1) {
        if (count >= capacity) {
            capacity *= 2;
            *arr_ptr = realloc(*arr_ptr, capacity * sizeof(int));
        }
        (*arr_ptr)[count] = num;
        count++;
#ifdef DEBUG
        printf("Filling arr: count %d, capacity %d\n", count, capacity);
#endif
    }

    if (count < capacity) {
        *arr_ptr = realloc(*arr_ptr, count * sizeof(int));
    }

    return count;
}

#ifdef DEBUG
void print_arr(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
#endif

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
    if (thread_count <= 0) {
        fprintf(stderr, "Number of threads must be a positive integer\n");
        return 1;
    }

    int** arr_ptr = malloc(sizeof(int*));
    int size = scan_arr(arr_ptr);
    int* arr = *arr_ptr;

#ifdef DEBUG
    printf("Array size: %d\n", size);
    print_arr(arr, size);
#endif

    // TODO: gen thread data

    // TODO: launch

    // TODO: print

    free(*arr_ptr);
    free(arr_ptr);

    return 0;
}
