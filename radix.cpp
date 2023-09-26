/*
Jordan Dehmel, 2023
jdehmel@outlook.com
*/

#include "radix.hpp"

void __radixSort(unsigned long long *array, const unsigned long long size, sort_data &data);
void __radixSort(string *array, const unsigned long long size, sort_data &data);

// Runs in time complexity O(n log_10(n)) w/ space O(n)
sort_data radixSort(unsigned long long *array, const unsigned long long size)
{
    // Build output sort_data object
    sort_data out;

    out.is_comparison_based = false;
    out.is_in_place = false;
    out.is_stable = true;
    out.name = "Numerical LSD Radix Sort";
    out.max_concurrent_bytes_used = 0;
    out.total_bytes_used = 0;
    out.array_accesses = 0;

    // The remaining members (IE swaps, comparisons)
    // are invalid for this algorithm.

    // Begin timer
    auto begin = chrono::high_resolution_clock::now();

    // Call internal version, passing output data object
    __radixSort(array, size, out);

    // End timer
    auto end = chrono::high_resolution_clock::now();
    out.execution_ns = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();

    // Return data
    return out;
}

// Runs in time complexity O(n log_26(n)) w/ space O(n)
// String version
sort_data radixSort(string *array, const unsigned long long size)
{
    // Build output sort_data object
    sort_data out;

    out.is_comparison_based = false;
    out.is_in_place = false;
    out.is_stable = true;
    out.name = "String-Based LSD Radix Sort";
    out.max_concurrent_bytes_used = 0;
    out.total_bytes_used = 0;
    out.array_accesses = 0;

    // The remaining members (IE swaps, comparisons)
    // are invalid for this algorithm.

    // Begin timer
    auto begin = chrono::high_resolution_clock::now();

    // Call internal version, passing output data object
    __radixSort(array, size, out);

    // End timer
    auto end = chrono::high_resolution_clock::now();
    out.execution_ns = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();

    // Return data
    return out;
}

////////////////////////////////////////////////////////////////

// Internal call
// Writes into data
void __radixSort(unsigned long long *array, const unsigned long long size, sort_data &data)
{
    // Dynamically allocate an output array of size size
    unsigned long long *out_array = nullptr;
    out_array = new unsigned long long[size];

    if (out_array == nullptr)
    {
        throw runtime_error("Failed to allocate auxillary array space during LSD Radix sort.");
    }

    data.total_bytes_used += size * sizeof(unsigned long long);
    if (size * sizeof(unsigned long long) > data.max_concurrent_bytes_used)
    {
        data.max_concurrent_bytes_used = size * sizeof(unsigned long long);
    }

    // Create counting array
    unsigned long long aux[10];

    data.total_bytes_used += 10 * sizeof(unsigned long long);
    if (10 * sizeof(unsigned long long) > data.max_concurrent_bytes_used)
    {
        data.max_concurrent_bytes_used = 10 * sizeof(unsigned long long);
    }

    // Get max
    unsigned long long max = array[0];
    for (unsigned long long i = 1; i < size; i++)
    {
        data.array_accesses++;
        if (array[i] > max)
        {
            data.array_accesses++;
            max = array[i];
        }
    }

    // Iterate through digits from LSD
    for (unsigned long long divisor = 1; divisor < max; divisor *= 10)
    {
        // Initialize counting array
        for (int i = 0; i < 10; i++)
        {
            data.array_accesses++;
            aux[i] = 0;
        }

        // Build counting array
        for (unsigned long long i = 0; i < size; i++)
        {
            data.array_accesses += 2;
            aux[(array[i] / divisor) % 10]++;
        }

        // Turn counting array into cumulate array
        unsigned long long temp, sum = 0;
        for (int i = 0; i < 10; i++)
        {
            data.array_accesses += 2;

            temp = aux[i];
            aux[i] = sum;
            sum += temp;
        }

        // Iterate through input array
        for (unsigned long long i = 0; i < size; i++)
        {
            // Place each item in its output place
            data.array_accesses += 6;

            out_array[aux[(array[i] / divisor) % 10]] = array[i];
            aux[(array[i] / divisor) % 10]++;
        }

        // Iterate through temp array, moving items back into main array
        for (unsigned long long i = 0; i < size; i++)
        {
            data.array_accesses += 2;
            array[i] = out_array[i];
        }
    }

    // Free dynamically allocated memory
    delete[] out_array;

    return;
}

////////////////////////////////////////////////////////////////

// Internal call
// Writes into data
// String version cuz I'm dumb
void __radixSort(string *array, const unsigned long long size, sort_data &data)
{
    // Dynamically allocate an output array of size size
    string *out_array = nullptr;
    out_array = new string[size];

    if (out_array == nullptr)
    {
        throw runtime_error("Failed to allocate auxillary array space during String-Based LSD Radix sort.");
    }

    data.total_bytes_used += size * sizeof(unsigned long long);
    if (size * sizeof(unsigned long long) > data.max_concurrent_bytes_used)
    {
        data.max_concurrent_bytes_used = size * sizeof(unsigned long long);
    }

    // Create counting array
    unsigned long long aux[255];

    data.total_bytes_used += 255 * sizeof(unsigned long long);
    if (255 * sizeof(unsigned long long) > data.max_concurrent_bytes_used)
    {
        data.max_concurrent_bytes_used = 255 * sizeof(unsigned long long);
    }

    // Get max length
    string &max = array[0];
    for (unsigned long long i = 1; i < size; i++)
    {
        data.array_accesses++;
        if (array[i].size() > max.size())
        {
            data.array_accesses++;
            max = array[i];
        }
    }

    // Iterate through digits from LSD
    for (unsigned long long charFromBack = 0; charFromBack < max.size(); charFromBack++)
    {
        // Initialize counting array
        for (int i = 0; i < 255; i++)
        {
            data.array_accesses++;
            aux[i] = 0;
        }

        // Build counting array
        for (unsigned long long i = 0; i < size; i++)
        {
            data.array_accesses += 2;
            aux[(unsigned char)array[i][array[i].size() - 1 - charFromBack]]++;
        }

        // Turn counting array into cumulate array
        unsigned long long temp, sum = 0;
        for (int i = 0; i < 255; i++)
        {
            data.array_accesses += 2;

            temp = aux[i];
            aux[i] = sum;
            sum += temp;
        }

        // Iterate through input array
        for (unsigned long long i = 0; i < size; i++)
        {
            // Place each item in its output place
            data.array_accesses += 6;

            out_array[aux[array[i][array[i].size() - 1 - charFromBack]]] = array[i];
            aux[array[i][array[i].size() - 1 - charFromBack]]++;
        }

        // Iterate through temp array, moving items back into main array
        for (unsigned long long i = 0; i < size; i++)
        {
            data.array_accesses += 2;
            array[i] = out_array[i];
        }
    }

    // Free dynamically allocated memory
    delete[] out_array;

    return;
}
