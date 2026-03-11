//
// Created by nosokvkokose on 10.03.26.
//

#include <math.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int elem_end;  // exclusive
    int elem_start;
    int* arr;
} pthrData_t;

typedef struct sortBranch_t sortBranch_t;

struct sortBranch_t {
    pthrData_t* data;
    sortBranch_t* left;  // NULL at bottom layer
    sortBranch_t* right;
};

// TODO: implement
void* merge_sort(void* data);

void build_sort_tree(sortBranch_t* root, pthrData_t* data,
    const int layer, const int depth) {
    root->data = data;

    if (layer == depth) {
        root->left = NULL;
        root->right = NULL;
        return;
    }

    int size = data->elem_end - data->elem_start;
    int left_size = size / 2;
    int right_size = size - left_size;

    pthrData_t* left_data = malloc(sizeof(pthrData_t));
    left_data->arr = data->arr;
    left_data->elem_start = data->elem_start;
    left_data->elem_end = data->elem_start + left_size;

    pthrData_t* right_data = malloc(sizeof(pthrData_t));
    right_data->arr = data->arr;
    right_data->elem_start = data->elem_start + left_size;
    right_data->elem_end = data->elem_end;

    // Recursively build left and right subtrees
    root->left = malloc(sizeof(sortBranch_t));
    root->right = malloc(sizeof(sortBranch_t));
    build_sort_tree(root->left, left_data, layer + 1, depth);
    build_sort_tree(root->right, right_data, layer + 1, depth);
}

// Sorts arr using thread_cnt threads
void launch_thread_sorts(int *arr, const int size, int thread_cnt) {
    if (thread_cnt > 2 * size - 1) {
        thread_cnt = 2 * size - 1;  // Ensure no empty threads
    }

    const int depth = log2(thread_cnt);

    pthrData_t data;
    data.arr = arr;
    data.elem_start = 0;
    data.elem_end = size;

    // Merge into tree
    sortBranch_t root;
    build_sort_tree(&root, &data, 1, depth);

    // Sort
    pthread_t* main_thread = malloc(sizeof(pthread_t));
    pthread_create(main_thread, NULL,  merge_sort, &root);

    free(main_thread);
}

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
        printf("Filling arr: count %d, capacity %d\n, elem %d", count, capacity, num);
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

    launch_thread_sorts(arr, size, thread_count);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(*arr_ptr);
    free(arr_ptr);

    return 0;
}
