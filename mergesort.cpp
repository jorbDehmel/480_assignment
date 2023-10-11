#include "mergesort.hpp"

#define ULL unsigned long long

void mergesort(unsigned long long *array, const unsigned long long size, sort_data out);
void merge(unsigned long long *array, const unsigned long long left, const unsigned long long mid,
           const unsigned long long right);
void mergesort(unsigned long long *array, const unsigned long long begin, const unsigned long long end, sort_data out);



sort_data mergesort(unsigned long long *array, const unsigned long long size){
	// Build output sort_data object
    sort_data out;

    out.is_comparison_based = false;
    out.is_in_place = false;
    out.is_stable = true;
    out.name = "Merge Sort";
    out.max_concurrent_bytes_used = 0;
    out.total_bytes_used = 0;
    out.array_accesses = 0;
    out.input_size = size;

    // The remaining members (IE swaps, comparisons)
    // are invalid for this algorithm.

    // Begin timer
    auto begin = chrono::high_resolution_clock::now();

    // Call internal version, passing output data object
    mergesort(array, 0, size, out);

    // End timer
    auto end = chrono::high_resolution_clock::now();
    out.execution_ns = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();

    // Return data
    return out;
}

// void mergesort(unsigned long long *array, const unsigned long long size, sort_data out)
// {
// 	mergeSort(array,0,size);
// }

void merge(unsigned long long *array, const unsigned long long left, const unsigned long long mid,
           const unsigned long long right)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;
 
    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];
 
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
 
    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;
 
    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne
           && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne]
            <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
 
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
            = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
 
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
            = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}
 
// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergesort(unsigned long long *array, const unsigned long long begin, const unsigned long long end, sort_data out)
{
    if (begin >= end)
        return;
 
    int mid = begin + (end - begin) / 2;
    mergesort(array, begin, mid, out);
    mergesort(array, mid + 1, end, out);
    merge(array, begin, mid, end);
}