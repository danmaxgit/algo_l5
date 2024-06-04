#include "stdio.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/ucontext.h>

void shaker_sort(int* array, size_t size, int* compare, int* swap) {
    int left = 0,
        right = size - 1,
        index_min = -1,
        index_max = -1,
        min = INT32_MAX,
        max = INT32_MIN,
        temp = 0;
    while (left < right) {
        for (int i =  left; i < right; i++) {
            if (array[i] < min) {
                index_min = i;
                min = array[i];
                *compare += 1;
            }
            if (array[i] > max) {
                index_max = i;
                max = array[i];
                *compare += 1;
            }
        }
        temp = array[index_min];
        array[index_min] = array[left];
        array[left] = temp;
        temp = array[index_max];
        array[index_max] = array[right];
        array[right] = temp;
        *swap += 2;
        left++;
        right--;
        min = INT32_MAX;
        max = INT32_MIN;
    }
}

int get_by_index(int* array, int n, int index){
    if (index >= 0 && index < n) {
        return array[index];
    }
    fprintf(stderr, "invalid index");
    return INT32_MAX;
}

int get_by_value(int* array, size_t n, int value){
    for (size_t i = 0; i < n; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    fprintf(stderr, "value not found");
    return -1;
}

void insert_by_index(size_t *n, int* array, int value, size_t index){
    *n += 1;
    array = (int *)realloc(array, sizeof(int) * *n);
    for (size_t i = index; i < *n - 1; i++) {
        array[i + 1] = array[i];
    }
    array[index] = value;
}
void insert(size_t *n, int* array, int value) {
    *n += 1;
    array = (int *)realloc(array, sizeof(int) * *n);
    array[*n - 1] = value;
    int trash, temp;
    shaker_sort(array, *n, &temp, &trash);
}

void remove_element(int* array, size_t* n, int index){
    for (size_t i = index; i < *n - 1; i++) {
        array[i] = array[i + 1];
    }
    *n -= 1;
    array = (int *)realloc(array, sizeof(int) * *n);
    int trash, temp;
    shaker_sort(array, *n, &trash, &temp);
}

int main(){
    size_t n = 10;
    int compare_num = 0,
        swap_num = 0;
    // scanf("%ld", &n);
    int *array = (int *)malloc(sizeof(int) * n);
    for (size_t i = 0; i < n; i++) {
        array[i] = rand() % 100;
    }
    for (size_t i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    shaker_sort(array, n, &compare_num, &swap_num);
    for (size_t i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    printf("com = %d, swap = %d\n", compare_num, swap_num);
    free(array);
    return 0;
}