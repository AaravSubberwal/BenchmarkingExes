#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Binary search implementation
bool binarySearch(const int* arr, int size, int target) {
    int left = 0;
    int right = size - 1;
    
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
    
    if (argc > 1) dataSize = atoi(argv[1]);
    if (argc > 2) searchCount = atoi(argv[2]);
    
    // Generate sorted data
    printf("Generating sorted array of %d integers...\n", dataSize);
    int* data = (int*)malloc(dataSize * sizeof(int));
    if (!data) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    // Fill with sequential numbers
    for (int i = 0; i < dataSize; i++) {
        data[i] = i * 2; // Even numbers to allow for "missing" odd numbers
    }
    
    // Initialize random number generator
    srand((unsigned int)time(NULL));
    
    // Perform searches
    printf("Performing %d binary searches...\n", searchCount);
    
    int found = 0;
    for (int i = 0; i < searchCount; i++) {
        int target = rand() % (dataSize * 2); // Some will be in array, some won't
        if (binarySearch(data, dataSize, target)) {
            found++;
        }
    }
    
    printf("Found %d values out of %d searches\n", found, searchCount);
    
    // Clean up
    free(data);
    return 0;
}