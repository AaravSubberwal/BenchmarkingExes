#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000

void quicksort(int arr[], int low, int high) {
    if (low >= high) return;

    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    int tmp = arr[i+1]; arr[i+1] = arr[high]; arr[high] = tmp;

    quicksort(arr, low, i);
    quicksort(arr, i + 2, high);
}

int main() {
    int* arr = malloc(N * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < N; ++i)
        arr[i] = rand();
    quicksort(arr, 0, N - 1);
    free(arr);
    return 0;
}
