/*
Coding group assignment, CSCI 480
Prof. Sherine Antoun
2023
*/

#include <cassert>

#include "sort_requirements.hpp"

#include "heapsort.hpp"
#include "mergesort.hpp"
#include "p_queue.hpp"
#include "radix.hpp"

#define NUM_RESULTS 4
#define ARRAY_SIZE 1000
#define OUTPUT_FILEPATH "output.txt"

int main(int argc, char *argv[])
{
    assert(argc == 2);

    // Initialize results
    sort_data results[NUM_RESULTS];

    // Heapsort testing here

    // Mergesort testing here

    // Priority queue testing here
    PriorityQueue<int> queue;
    srand(time(NULL));
    for (int i = 0; i < 1000; i++)
    {
        queue.insert(rand() % 10000);
    }
    int max = queue.deleteMax();
    while (!queue.empty())
    {
        int next = queue.deleteMax();
        if (max < next)
        {
            break;
        }
        max = next;
    }
    if (queue.empty())
    {
        cout << "Queue works.\n";
    }
    else
    {
        cout << "ERROR: Queue broken.\n";
    }

    {
        // Radix sort testing here
        unsigned long long array[ARRAY_SIZE];
        srand(time(NULL));
        for (int i = 0; i < 1000; i++)
        {
            array[i] = rand() % 10000;
        }

        results[NUM_RESULTS - 2] = radixSort(array, ARRAY_SIZE);

        if (isSorted(array, ARRAY_SIZE))
        {
            cout << "Successfully sorted.\n";
        }
        else
        {
            cout << "ERROR! List is not sorted.\n";
        }
    }

    {
        // String radix sort testing here
        string array[ARRAY_SIZE];
        srand(time(NULL));
        for (int i = 0; i < 1000; i++)
        {
            array[i] = "AAAAA";

            for (int c = 0; c < array[i].size(); c++)
            {
                array[i][c] += rand() % ('Z' - 'A');
            }
        }

        results[NUM_RESULTS - 1] = radixSort(array, ARRAY_SIZE);

        if (isSorted(array, ARRAY_SIZE))
        {
            cout << "Successfully sorted.\n";
        }
        else
        {
            cout << "ERROR! List is not sorted.\n";
        }
    }

    // Output stuff
    ofstream file(OUTPUT_FILEPATH);
    assert(file.is_open());

    for (int i = 0; i < NUM_RESULTS; i++)
    {
        file << results[i].name << ":\n"
             << "Stable:\t" << (results[i].is_stable ? "true" : "false") << '\n'
             << "In-place:\t" << (results[i].is_in_place ? "true" : "false") << '\n';

        if (results[i].is_comparison_based)
        {
            file << "Number comparisons:\t" << results[i].comparisons << '\n'
                 << "Number swaps:\n"
                 << results[i].swaps << '\n';
        }
        else
        {
            file << "Number array accesses:\t" << results[i].array_accesses << '\n';
        }

        file << "Execution nanoseconds:\t" << results[i].execution_ns << '\n'
             << "Execution milliseconds:\t" << (results[i].execution_ns / 1000000.0) << '\n'
             << "Max concurrent bytes used:\t" << results[i].max_concurrent_bytes_used << '\n'
             << "Total bytes used:\t" << results[i].total_bytes_used << '\n';

        file << "\n\n";
    }

    file.close();

    return 0;
}
