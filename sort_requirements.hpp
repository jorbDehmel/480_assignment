/*
File outlining some basic aspects of our
sorting algorithms.
*/

#ifndef SORT_REQ_HPP
#define SORT_REQ_HPP

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <cmath>
using namespace std;

// Each sorting algorithm should return one of these
// Try not to modify this struct, but if you need to,
// only ADD members (do not remove them).
struct sort_data
{
    // Attributes of all sorts
    string name = "";
    unsigned long long execution_ns = 0;
    bool is_stable = false;
    bool is_in_place = false;
    bool is_comparison_based = true;

    unsigned long long input_size = 0;

    // For comparison-based sorts
    unsigned long long comparisons = 0;
    unsigned long long swaps = 0;

    // For non-comparison sorts
    unsigned long long array_accesses = 0;

    /*
    If you allocate 15 100-byte arrays,
    deleting the previous before making
    the next, the total bytes used is
    1500, while the maximum concurrent
    bytes used is 100.
    */
    unsigned long long total_bytes_used = 0;
    unsigned long long max_concurrent_bytes_used = 0;
};

// Compare two objects and update the associated sort_data
// Returns -1 if left is less than right, 1 if left is greater
// than right, 0 if they are equal.
template <class T>
int compare(const T &left, const T &right, sort_data &data)
{
    data.comparisons++;

    if (left < right)
    {
        return -1;
    }
    else if (left == right)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Swap and update the associated sort_data
template <class T>
void swapArrayElems(T *left, T *right, sort_data &data)
{
    T temp = *left;
    *left = *right;
    *right = temp;

    data.swaps++;

    return;
}

template <class T>
bool isSorted(const T *array, const unsigned long long &size)
{
    for (unsigned long long i = 0; i < size - 1; i++)
    {
        if (array[i] > array[i + 1])
        {
            cout << "Unsorted at index " << i << '\n';
            return false;
        }
    }

    return true;
}

#endif
