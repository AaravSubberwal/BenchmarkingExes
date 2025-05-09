#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define N 1000000

void merge(std::vector<int>& arr, int l, int m, int r) {
    std::vector<int> L(arr.begin() + l, arr.begin() + m + 1);
    std::vector<int> R(arr.begin() + m + 1, arr.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while (i < L.size() && j < R.size())
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];
}

void mergesort(std::vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergesort(arr, l, m);
    mergesort(arr, m + 1, r);
    merge(arr, l, m, r);
}

int main() {
    std::vector<int> arr(N);
    srand((unsigned)time(0));
    for (int& x : arr)
        x = rand();

    mergesort(arr, 0, N - 1);
    return 0;
}
