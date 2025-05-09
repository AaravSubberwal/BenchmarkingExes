#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

const int dataSize = 10000000;
const int searchCount = 1000;

int fibonacci_search(const std::vector<int>& arr, int x) {
    int n = arr.size();
    int fibMMm2 = 0, fibMMm1 = 1, fibM = fibMMm1 + fibMMm2;

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm1 + fibMMm2;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = std::min(offset + fibMMm2, n - 1);

        if (arr[i] < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (arr[i] > x) {
            fibM = fibMMm2;
            fibMMm1 -= fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            return i;
        }
    }

    if (fibMMm1 && arr[offset + 1] == x)
        return offset + 1;

    return -1;
}

int main() {
    std::vector<int> data(dataSize);
    srand((unsigned)time(0));
    for (int& x : data)
        x = rand();

    std::sort(data.begin(), data.end());

    for (int i = 0; i < searchCount; ++i) {
        int target = rand();
        fibonacci_search(data, target);
    }

    return 0;
}
