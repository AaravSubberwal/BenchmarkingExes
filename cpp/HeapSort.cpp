#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define N 1000000

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i, l = 2*i + 1, r = 2*i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapsort(std::vector<int>& arr, int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n-1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    std::vector<int> arr(N);
    srand((unsigned)time(0));
    for (int& x : arr)
        x = rand();

    heapsort(arr, N);
    return 0;
}
