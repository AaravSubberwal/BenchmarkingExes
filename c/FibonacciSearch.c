#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATASIZE 10000000
#define SEARCHCOUNT 1000

int fibonacci_search(int arr[], int x, int n) {
    int fibMMm2 = 0, fibMMm1 = 1, fibM = fibMMm1 + fibMMm2;
    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm1 + fibMMm2;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = (offset + fibMMm2 < n - 1) ? offset + fibMMm2 : n - 1;

        if (arr[i] < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (arr[i] > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            return i;
        }
    }

    if (fibMMm1 && arr[offset + 1] == x)
        return offset + 1;

    return -1;
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int* data = malloc(sizeof(int) * DATASIZE);
    srand(time(NULL));

    for (int i = 0; i < DATASIZE; ++i)
        data[i] = rand();
    qsort(data, DATASIZE, sizeof(int), compare);

    for (int i = 0; i < SEARCHCOUNT; ++i) {
        int target = rand();
        fibonacci_search(data, target, DATASIZE);
    }

    free(data);
    return 0;
}
