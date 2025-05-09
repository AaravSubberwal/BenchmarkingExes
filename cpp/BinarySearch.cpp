#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

// Binary search implementation
bool binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target)
            return true;
        
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    
    return false;
}

int main(int argc, char* argv[]) {
    // Parse command line arguments
    int dataSize = 10000000; // Default size
    int searchCount = 1000;  // Default search count
    
    if (argc > 1) dataSize = std::stoi(argv[1]);
    if (argc > 2) searchCount = std::stoi(argv[2]);
    
    // Generate sorted data
    std::cout << "Generating sorted array of " << dataSize << " integers...\n";
    std::vector<int> data(dataSize);
    
    // Fill with sequential numbers
    for (int i = 0; i < dataSize; i++) {
        data[i] = i * 2; // Even numbers to allow for "missing" odd numbers
    }
    
    // Perform searches
    std::cout << "Performing " << searchCount << " binary searches...\n";
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> valueRange(0, dataSize * 2); // Some will be in array, some won't
    
    int found = 0;
    for (int i = 0; i < searchCount; i++) {
        int target = valueRange(gen);
        if (binarySearch(data, target)) {
            found++;
        }
    }
    
    std::cout << "Found " << found << " values out of " << searchCount << " searches\n";
    return 0;
}