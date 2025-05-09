#include <iostream>
#include <vector>
using namespace std;

int max_subarray_sum(const vector<int>& arr) {
    int max_sum = arr[0];
    int current_sum = arr[0];

    for (int i = 1; i < arr.size(); ++i) {
        current_sum = max(current_sum + arr[i], arr[i]);
        max_sum = max(max_sum, current_sum);
    }

    return max_sum;
}

int main() {
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Maximum Subarray Sum: " << max_subarray_sum(arr) << endl;
    return 0;
}
