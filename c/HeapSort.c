#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000

void heapify(int arr[], int n, int i) {
    int largest = i, l = 2*i + 1, r = 2*i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        int tmp = arr[i]; arr[i] = arr[largest]; arr[largest] = tmp;
        heapify(arr, n, largest);
    }
}

void heapsort(int arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n-1; i > 0; i--) {
        int tmp = arr[0]; arr[0] = arr[i]; arr[i] = tmp;
        heapify(arr, i, 0);
    }
}

int main() {
    int* arr = malloc(N * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < N; ++i)
        arr[i] = rand();

    heapsort(arr, N);
    free(arr);
    return 0;
}
