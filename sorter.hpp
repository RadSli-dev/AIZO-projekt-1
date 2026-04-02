#pragma once
#include "vector.hpp"
#include "heap.hpp"

class sorter{
public:
    //comp ma zwracać odpowiedź na zapytanie o pierwszy argument względem drugiego -> jeżeli chcemy zapytać o to czy l > r to comp(l,r) powinien zwracać true
    template <typename T, typename Func>
    static void heap_sort(heap<T>& arr, Func comp){
        for (std::size_t i = arr.arr.len()-1; i > 0; --i){
            arr.swap(i,0);
            --arr.heapSize;
            arr.heapify(0, comp);
        }
    }

    template <typename T, typename Func>
    static void shell_sort(vector<T>& arr, Func comp){

    }
    template <typename T, typename Func>
    static void quick_sort(vector<T>& arr, std::size_t left, std::size_t right, Func pivot_select){
        //Correct bound check and default recursion case
        if (left >= arr.len() || right >= arr.len())
            throw std::invalid_argument("Err: quick_sort bounds are outside vector boundary");
        if (left >= right)
            return;

        //pivot selection
        size_t pivot_index = pivot_select(arr, left, right);
        if (pivot_index < left || pivot_index > right)
            throw std::invalid_argument("Err: pivot_select returned invalid pivot index");

        pivot_index = sorter::partition(arr, left, right, pivot_index);

        //recursive quick_sort call guarded by if statements to ensure correct bounds
        if (pivot_index > left)
            quick_sort(arr, left, pivot_index - 1, pivot_select);
        if (pivot_index < right)
            quick_sort(arr, pivot_index + 1, right, pivot_select);
    }

    template <typename T>
    static std::size_t partition(vector<T>& arr, std::size_t left, std::size_t right, std::size_t pivot_index){
        //keep pivot safe from swaps and store it at the end of the vector
        T pivot = arr[pivot_index];
        arr.swap(pivot_index, right);

        //scan array for elements <= pivot and put them on the left side of the vector.
        //store_index keeps the bounds of the left side
        std::size_t store_index = left;
        for (std::size_t i = left; i < right; ++i){
            if (arr[i] <= pivot){
                arr.swap(i, store_index);
                ++store_index;
            }
        }

        //put pivot back into correct place
        arr.swap(store_index, right);
        //arr.print(left, right);
        return store_index;
    }
};