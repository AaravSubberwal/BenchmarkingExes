#include <stdio.h>
#include <stdlib.h>

int max_subarray_sum(int* arr, int size) {
    int max_sum = arr[0];
    int current_sum = arr[0];

    for (int i = 1; i < size; ++i) {
        current_sum = (current_sum + arr[i] > arr[i]) ? current_sum + arr[i] : arr[i];
        max_sum = (max_sum > current_sum) ? max_sum : current_sum;
    }

    return max_sum;
}

int main() {
    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum Subarray Sum: %d\n", max_subarray_sum(arr, size));
    return 0;
}
