#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATASIZE 10000000
#define SEARCHCOUNT 1000

int linear_search(int* arr, int n, int target) {
    for (int i = 0; i < n; ++i)
        if (arr[i] == target)
            return i;
    return -1;
}

int main() {
    int* data = malloc(sizeof(int) * DATASIZE);
    srand(time(NULL));

    for (int i = 0; i < DATASIZE; ++i)
        data[i] = rand();

    for (int i = 0; i < SEARCHCOUNT; ++i) {
        int target = rand();
        linear_search(data, DATASIZE, target);
    }

    free(data);
    return 0;
}
