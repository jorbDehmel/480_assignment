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
#define OUTPUT_FILEPATH ""

int main(int argc, char *argv[])
{
    assert(argc == 2);

    // Initialize results
    sort_data results[NUM_RESULTS];

    // Heapsort testing here

    // Mergesort testing here

    // Priority queue testing here

    // Radix sort testing here

    // Output stuff
    ofstream file(OUTPUT_FILEPATH);
    assert(file.is_open());

    for (int i = 0; i < NUM_RESULTS; i++)
    {
        file << results[i].name << ":\n"
             << "Stable:\t" << (results[i].is_stable ? "true" : "false") << '\n'
             << "In-place:\t" << (results[i].is_in_place ? "true" : "false") << '\n';
    }

    file.close();

    return 0;
}
