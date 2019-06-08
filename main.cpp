#include <iostream>
#include <cstdlib>
#include <utility>
#include <cassert>

template<typename T>
void print_array(T* arr, uint64_t length) {
    for (uint64_t idx = 0; idx < length; ++idx) {
        std::cout << arr[idx] << "\t";
    }
    std::cout << std::endl;
}

template<typename T, typename functor>
void quicksort (T* first, uint64_t length, functor pivot_func) {
    // print_array(first, length);
    T pivot = pivot_func(first, length);
    T* border = first;
    T* next = border;

    for (uint64_t idx = 0; idx < length; ++idx, ++next) {
        if (*next <= pivot) {
            std::swap(*next, *border);
            ++border;
        }
    }

    uint64_t sort_len = border - first - 1;
    // print_array(first, length);
    if (sort_len > 1 && border != first)  // sort_len is unsigned value (-1 more than length)
        quicksort(first, sort_len, pivot_func);
    sort_len = length - (border - first);
    if (sort_len > 1)
        quicksort(border, sort_len, pivot_func);
    // print_array(first, length);
}

template<typename T>
T get_pivot_last(T* first, uint64_t length) {
    return first [length - 1];
}

template<typename T>
T get_pivot_random(T* first, uint64_t length) {
    uint64_t idx = std::rand()%length;
    std::swap(first[idx], first[length-1]);
    return first[length-1];
}

uint64_t* gen_array(uint64_t length) {
    uint64_t* new_array = new uint64_t[length];
    for (uint64_t idx = 0; idx < length; ++idx) {
        new_array[idx] = std::rand() % length;
    }
    return new_array;
}

int main()
{
    uint64_t length = 20;
    uint64_t* arr = gen_array(length);
    print_array(arr, length);
    quicksort<uint64_t>(arr, length, get_pivot_last<uint64_t>);
    print_array(arr, length);
    delete [] arr;

    std::cout << std::endl;

    arr = gen_array(length);
    print_array(arr, length);
    quicksort<uint64_t>(arr, length, get_pivot_random<uint64_t>);
    print_array(arr, length);
    delete [] arr;

    return 0;
}
