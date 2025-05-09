#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

#define N 1000000

void quicksort(std::vector<int>& arr, int low, int high) {
    if (low >= high) return;

    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i+1], arr[high]);

    quicksort(arr, low, i);
    quicksort(arr, i + 2, high);
}

int main() {
    std::vector<int> arr(N);
    srand((unsigned)time(0));
    for (int& x : arr)
        x = rand();

    quicksort(arr, 0, N - 1);

    return 0;
}
