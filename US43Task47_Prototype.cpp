#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <forward_list>
#include <ctime>
#include <chrono>

using namespace std::chrono;

/*
 *
 *
 *
 *
 */

template <class ForwardIt>
    void quicksort(ForwardIt first, ForwardIt last)
    {
        if(first==last) return;
        auto pivot = *next(first, distance(first,last)/2);
        ForwardIt middle1 = std::partition(first, last, [pivot](const auto& em){return em < pivot;});
        ForwardIt middle2 = std::partition(middle1, last,
                            [pivot](const auto& em){return !(pivot < em);});
        quicksort(first, middle1);
        quicksort(middle2, last);
}

int main()
{
    auto start = high_resolution_clock::now();

    int NUM_ROWS = 100;
    int NUM_COLS = 5;

    int* A = new int[NUM_ROWS * NUM_COLS];

    for (int i = 0; i < NUM_ROWS; i++)
        for (int j = 0; j < NUM_COLS; j++)
            *(A + i*NUM_COLS + j) = rand() % NUM_ROWS;


    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
            std::cout << *(A + i*NUM_COLS + j) << " ";
        std::cout << std::endl;
    }

    std::vector<int> *ptr = *A;

    auto it = std::partition(ptr[2], ptr[498], [](int i){return i % 2 == 0;});

    copy(*(A + 4), it, std::ostream_iterator<int>(std::cout, " "));
    std::cout << " * " ;
    copy(it, *(A + 103), std::ostream_iterator<int>(std::cout, " "));

    delete[]A;

    return 0;
}
