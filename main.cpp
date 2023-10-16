/*
Coding group assignment, CSCI 480
Prof. Sherine Antoun
2023
*/

/*
TODO:
- Mergesort writeup
- Priority queue sort writeup
*/

#include <cassert>
#include <cstring>

#include "sort_requirements.hpp"

#include "heapsort.hpp"
#include "mergesort.hpp"
#include "p_queue.hpp"
#include "radix.hpp"

#define NUM_RESULTS 6
#define ARRAY_SIZE 1000

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Error: Please provide input and output filepaths as command line arguments.\n";
        return 1;
    }

    // Initialize results
    sort_data results[NUM_RESULTS];

    {
        // Heapsort testing here
        unsigned long long array[ARRAY_SIZE];
        srand(time(NULL));
        for (int i = 0; i < 1000; i++)
        {
            array[i] = rand() % 10000;
        }

        results[NUM_RESULTS - 6] = heapsort(array, ARRAY_SIZE);

        if (isSorted(array, ARRAY_SIZE))
        {
            cout << "[HeapSort]\t\tSuccessfully sorted.\n";
        }
        else
        {
            cout << "[HeapSort]\t\tERROR! List is not sorted.\n";
        }
    }

    // Mergesort testing here
    {
        unsigned long long array[ARRAY_SIZE];
        srand(time(NULL));
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            array[i] = rand() % ARRAY_SIZE;
        }

        results[NUM_RESULTS - 5] = mergesort(array, ARRAY_SIZE);

        if (isSorted(array, ARRAY_SIZE))
        {
            cout << "[MergeSort]\t\tSuccessfully sorted.\n";
        }
        else
        {
            // For debugging purposes
            cout << "Output of mergesort:";
            for (int i = 0; i < ARRAY_SIZE; i++)
            {
                if (i % 10 == 0)
                {
                    cout << "\n\t";
                }

                cout << array[i] << ' ';
            }
            cout << '\n';

            cout << "[MergeSort]\t\tERROR! List is not sorted.\n";
        }
    }

    // Priority queue testing here
    PriorityQueue<int> queue(ARRAY_SIZE);
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

    results[NUM_RESULTS - 4] = queue.get_data();
    if (queue.empty())
    {
        cout << "[Priority Queue]\tSuccessfully sorted.\n";
    }
    else
    {
        cout << "[Priority Queue]\tERROR: Queue broken.\n";
    }

    // Radix sort testing here
    {
        unsigned long long array[ARRAY_SIZE];
        srand(time(NULL));
        for (int i = 0; i < 1000; i++)
        {
            array[i] = rand() % 10000;
        }

        results[NUM_RESULTS - 3] = radixSort(array, ARRAY_SIZE);

        if (isSorted(array, ARRAY_SIZE))
        {
            cout << "[Int RadixSort]\t\tSuccessfully sorted.\n";
        }
        else
        {
            cout << "[Int RadixSort]\t\tERROR! List is not sorted.\n";
        }
    }

    // String radix sort testing here
    {
        ifstream inputFile(argv[1]);
        if (!inputFile.is_open())
        {
            throw runtime_error("Failed to open input file for String-Based Radix Sort.");
        }

        string fullText, temp;
        while (!inputFile.eof())
        {
            inputFile >> temp;
            fullText.append(temp);
        }
        inputFile.close();

        string *array = nullptr;
        unsigned long long size = fullText.size() - 1;
        array = new string[size];

        for (int i = 0; i < size; i++)
        {
            array[i] = fullText.substr(i, 15);
        }

        results[NUM_RESULTS - 2] = radixSort(array, size);

        bool sorted = true;
        for (unsigned long long i = 0; i + 1 < size; i++)
        {
            if (array[i].size() > array[i + 1].size())
            {
                sorted = false;
                break;
            }
            else if (array[i].size() < array[i + 1].size())
            {
                continue;
            }
            else
            {
                if (array[i] > array[i + 1])
                {
                    sorted = false;
                    break;
                }
            }
        }

        if (sorted)
        {
            cout << "[LSD RadixSort]\t\tSuccessfully sorted.\n";
        }
        else
        {
            cout << "[LSD RadixSort]\t\tERROR! List is not sorted.\n";
        }

        delete[] array;
    }

    // MSD String radix sort testing here
    {
        ifstream inputFile(argv[1]);
        if (!inputFile.is_open())
        {
            throw runtime_error("Failed to open input file for String-Based Radix Sort.");
        }

        string fullText, temp;
        while (!inputFile.eof())
        {
            inputFile >> temp;
            fullText.append(temp);
        }
        inputFile.close();

        string *array = nullptr;
        unsigned long long size = fullText.size() - 1;
        array = new string[size];

        for (int i = 0; i < size; i++)
        {
            array[i] = fullText.substr(i, 15);
        }

        results[NUM_RESULTS - 1] = radixSortMSD(array, size);

        bool sorted = true;
        for (unsigned long long i = 0; i + 1 < size; i++)
        {
            if (array[i].size() > array[i + 1].size())
            {
                sorted = false;
                break;
            }
            else if (array[i].size() < array[i + 1].size())
            {
                continue;
            }
            else
            {
                for (int j = array[i].size() - 1; j >= 0; j--)
                {
                    if (array[i + 1][j] > array[i][j])
                    {
                        break;
                    }
                    else if (array[i + 1][j] < array[i][j])
                    {
                        sorted = false;
                        break;
                    }
                }
            }
        }

        if (sorted)
        {
            cout << "[MSD RadixSort]\t\tSuccessfully sorted.\n";
        }
        else
        {
            cout << "[MSD RadixSort]\t\tERROR! List is not sorted.\n";
        }

        delete[] array;
    }

    // Output stuff
    ofstream file(argv[2]);
    assert(file.is_open());

    for (int i = 0; i < NUM_RESULTS; i++)
    {
        if (results[i].name == "")
        {
            file << "[Result item left blank]\n\n\n";
            continue;
        }

        file << results[i].name << ":\n"
             << "Stable:\t" << (results[i].is_stable ? "true" : "false") << '\n'
             << "In-place:\t" << (results[i].is_in_place ? "true" : "false") << '\n'
             << "Input size:\t" << results[i].input_size << '\n';

        if (results[i].is_comparison_based)
        {
            file << "Number comparisons:\t" << results[i].comparisons << '\n'
                 << "Number swaps:\t"
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
