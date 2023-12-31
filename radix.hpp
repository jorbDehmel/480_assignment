// Jordan does this one

#ifndef RADIX_HPP
#define RADIX_HPP

#include "sort_requirements.hpp"

// Radix sort for numbers (cuz I didn't read the spec thoroughly enough)
sort_data radixSort(unsigned long long *array, const unsigned long long size);

// Corrected version for strings
sort_data radixSort(string *array, const unsigned long long size);

// MSD version of the string fn above
sort_data radixSortMSD(string *array, const unsigned long long size);

#endif
