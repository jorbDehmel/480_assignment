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
    out.input_size = size;

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
    out.input_size = size;

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

#define COUNTING_ARRAY_LENGTH 255

// Internal call
// Writes into data
// String version cuz I'm dumb
void __radixSort(string *array, const unsigned long long size, sort_data &data)
{
    // Create counting (aux) array (static)
    unsigned long long aux[COUNTING_ARRAY_LENGTH];

    data.total_bytes_used += COUNTING_ARRAY_LENGTH * sizeof(unsigned long long);
    if (COUNTING_ARRAY_LENGTH * sizeof(unsigned long long) > data.max_concurrent_bytes_used)
    {
        data.max_concurrent_bytes_used = COUNTING_ARRAY_LENGTH * sizeof(unsigned long long);
    }

    // Create output array (dynamic)
    string *output = nullptr;
    output = new string[size];
    if (output == nullptr)
    {
        throw runtime_error("Failed to allocate auxiliary array during LSD string radix sort.");
    }

    // We will count the dynamically allocated portion of this later.
    // This is for static allocation ONLY.
    data.total_bytes_used += size * sizeof(string);
    if (size * sizeof(string) > data.max_concurrent_bytes_used)
    {
        data.max_concurrent_bytes_used = size * sizeof(string);
    }

    // Get max number of digits
    long long maxLength = array[0].size();
    for (unsigned long long i = 1; i < size; i++)
    {
        data.array_accesses++;

        if (array[i].size() > maxLength)
        {
            data.array_accesses++;

            maxLength = array[i].size();
        }
    }

    // Iterate over digits
    for (long long i = -1; maxLength + i >= 0; i--)
    {
        // Initialize counting array
        for (int j = 0; j < COUNTING_ARRAY_LENGTH; j++)
        {
            data.array_accesses++;

            aux[j] = 0;
        }

        // Iterate over input array, building counting array
        for (unsigned long long j = 0; j < size; j++)
        {
            // If in range
            data.array_accesses++;
            if ((long long)array[j].size() + i >= 0)
            {
                data.array_accesses += 4;
                aux[(unsigned char)array[j][(long long)array[j].size() + i]]++;
            }

            // If not in range
            else
            {
                data.array_accesses++;
                aux[0]++;
            }
        }

        // Turn counting array into cumulate array
        unsigned long long sum = 0;
        unsigned long long temp;

        for (int j = 0; j < COUNTING_ARRAY_LENGTH; j++)
        {
            data.array_accesses += 2;

            temp = aux[j];
            aux[j] = sum;
            sum += temp;
        }

        // Put items in correct spot
        for (long long j = 0; j < size; j++)
        {
            // If in range
            data.array_accesses++;
            if ((long long)array[j].size() + i >= 0)
            {
                data.array_accesses += 10;

                long long target = aux[(unsigned char)array[j][(long long)array[j].size() + i]];

                output[target] = array[j];
                aux[(unsigned char)array[j][(long long)array[j].size() + i]]++;
            }

            // If not in range
            else
            {
                data.array_accesses += 4;

                output[aux[0]] = array[j];
                aux[0]++;
            }
        }

        // Move output array back into input array
        for (unsigned long long j = 0; j < size; j++)
        {
            data.array_accesses += 2;
            array[j] = output[j];
        }
    }

    // Clean up trash
    delete[] output;

    // Get actual size of string array (this handles the dynamic
    // portion of strings. The static portion was handled earlier).
    // This analysis does not influence data.array_accesses, since
    // it is just for bookkeeping and not part of the algorithm.
    unsigned long long totalNumChars = 0;

    for (unsigned long long i = 0; i < size; i++)
    {
        totalNumChars += array[i].size();
    }

    data.total_bytes_used += totalNumChars * sizeof(char);
    if (totalNumChars * sizeof(char) > data.max_concurrent_bytes_used)
    {
        data.max_concurrent_bytes_used = totalNumChars * sizeof(char);
    }

    return;
}
