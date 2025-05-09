#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int dataSize = 10000000;
const int searchCount = 1000;

int linear_search(const std::vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); ++i)
        if (arr[i] == target)
            return i;
    return -1;
}

int main() {
    std::vector<int> data(dataSize);
    srand(time(0));

    for (int& x : data)
        x = rand();

    for (int i = 0; i < searchCount; ++i) {
        int target = rand();
        linear_search(data, target);
    }

    return 0;
}
