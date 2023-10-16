#include "mergesort.hpp"

#define ULL unsigned long long


void mergesort(unsigned long long *array, const unsigned long long begin, const unsigned long long end, sort_data& data);
void merge(unsigned long long *array, const unsigned long long left, const unsigned long long mid,
           const unsigned long long right, sort_data& data);


sort_data mergesort(unsigned long long *array, const unsigned long long size){
	// Build output sort_data object
    sort_data data;

    data.is_comparison_based = true;
    data.is_in_place = false;
    data.is_stable = true;
    data.name = "Merge Sort";
    data.max_concurrent_bytes_used = 0;
    data.total_bytes_used = 0;
    data.comparisons = 0;
    data.swaps = 0;
    data.input_size = size;

    // The remaining members (IE swaps, comparisons)
    // are invalid for this algorithm.

    // Begin timer
    auto begin = chrono::high_resolution_clock::now();

    // Call internal version, passing output data object
    mergesort(array, 0, size, data);

    // End timer
    auto end = chrono::high_resolution_clock::now();
    data.execution_ns = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();

    // Return data
    return data;
}


void merge(unsigned long long *array, const unsigned long long left, const unsigned long long mid,
           const unsigned long long right, sort_data& data)
{
    unsigned long long const leftSize = mid - left + 1;
    unsigned long long const rightSize = right - mid;
 
    // temp arrays
    auto *leftArray = new unsigned long long[leftSize],
         *rightArray = new unsigned long long[rightSize];
    
    //update sort data values
    data.total_bytes_used += (leftSize + rightSize) * sizeof(unsigned long long);
    if((leftSize + rightSize) * sizeof(unsigned long long) > data.max_concurrent_bytes_used){
        data.max_concurrent_bytes_used = (leftSize + rightSize) * sizeof(unsigned long long);
    }

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < leftSize; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < rightSize; j++)
        rightArray[j] = array[mid + 1 + j];
 
    unsigned long long indexOfLeft = 0, indexOfRight = 0;
    unsigned long long indexOfMerged = left;
 
    // Merge the temp arrays back into array[left..right]
    while (indexOfLeft < leftSize && indexOfRight < rightSize) {
        if (leftArray[indexOfLeft] <= rightArray[indexOfRight]) {
            array[indexOfMerged]= leftArray[indexOfLeft];
            indexOfLeft++;
        }
        else {
            array[indexOfMerged] = rightArray[indexOfRight];
            indexOfRight++;
        }
        indexOfMerged++;
        //Comparison of elements in array and assignment of element
        data.comparisons++;
        data.swaps++;
    }
 
    // Copy the remaining elements of left[]
    while (indexOfLeft < leftSize) {
        array[indexOfMerged] = leftArray[indexOfLeft];
        indexOfLeft++;
        indexOfMerged++;
        //just assignment of element
        data.swaps++;
    }
 
    // Copy the remaining elements of right[]
    while (indexOfRight < rightSize) {
        array[indexOfMerged] = rightArray[indexOfRight];
        indexOfRight++;
        indexOfMerged++;
        //just assignment of element
        data.swaps++;
    }
    delete[] leftArray;
    delete[] rightArray;
}
 
// begin is for left index and end is right index
void mergesort(unsigned long long *array, const unsigned long long begin, const unsigned long long end, sort_data& data)
{
    if (begin >= end)
        return;
 
    unsigned long long mid = begin + (end - begin) / 2;
    mergesort(array, begin, mid, data);
    mergesort(array, mid + 1, end, data);
    merge(array, begin, mid, end, data);
}