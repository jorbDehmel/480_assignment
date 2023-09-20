#ifndef SORT_REQ_HPP
#define SORT_REQ_HPP

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
using namespace std;

// Each sorting algorithm should return one of these
struct sort_data
{
    unsigned long long execution_ns = 0;
    unsigned long long comparisons = 0;
    unsigned long long swaps = 0;
    unsigned long long bytes_used = 0;

    bool is_stable = false;
    bool is_in_place = false;
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
void swap(T *left, T *right, sort_data &data)
{
    T temp = *left;
    *left = *right;
    *right = temp;

    data.swaps++;

    return;
}

#endif
