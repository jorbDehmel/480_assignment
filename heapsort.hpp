// Made by Logan

/**
 * @brief Builds a heap from an array
 * @param array The array to build a heap from
 * @param size The size of the array
 * @param data The sort_data associated with the sort
 * @return void
*/
template <class T>
void heapify(T *array, size_t size, size_t i, sort_data &data) {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    // If left child is larger than root
    if (left < size && compare(array[left], array[largest], data) > 0) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < size && compare(array[right], array[largest], data) > 0) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        swapArrayElems(&array[i], &array[largest], data);

        // update the total and concurrent bytes used
        data.total_bytes_used += sizeof(T) * 2;
        data.max_concurrent_bytes_used = max(data.max_concurrent_bytes_used, data.total_bytes_used);

        // Recursively heapify the affected sub-tree
        heapify(array, size, largest, data);
    }
}

/**
 * @brief Sorts an array using the heap sort algorithm
 * @param array The array to sort
 * @param size The size of the array
 * @return sort_data The sort_data associated with the sort
*/
template <class T>
sort_data heapsort(T *array, size_t size) {
    sort_data data;
    data.name = "Heap Sort";
    data.is_comparison_based = true;
    data.is_stable = false;
    data.is_in_place = true;
    data.input_size = size;
    data.max_concurrent_bytes_used = 0;
    data.total_bytes_used = 0;

    // Start the clock
    auto start = chrono::high_resolution_clock::now();

    // Build the max heap
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(array, size, i, data);
    }

    // Extract elements from the heap
    for (int i = size - 1; i >= 0; i--) {
        swapArrayElems(&array[0], &array[i], data);

        // update the total and concurrent bytes used
        data.total_bytes_used += sizeof(T) * 2;
        data.max_concurrent_bytes_used = max(data.max_concurrent_bytes_used, data.total_bytes_used);

        heapify(array, i, 0, data);
    }

    // Stop the clock
    auto stop = chrono::high_resolution_clock::now();

    // Calculate the elapsed time
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    data.execution_ns = duration.count();

    return data;
}
