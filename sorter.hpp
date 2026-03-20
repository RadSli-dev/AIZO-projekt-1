#pragma once
#include "vector.hpp"
#include "heap.hpp"

class sorter{
public:
    //comp ma zwracać odpowiedź na zapytanie o pierwszy argument względem drugiego -> jeżeli chcemy zapytać o to czy l > r to comp(l,r) powinien zwracać true
    template <typename T, typename Func>
    static void heap_sort(heap<T>& arr, Func comp){
        for (std::size_t i = arr.size()/2; i > 1; --i){
            arr.swap(i,1);
            --arr.heapSize;
            arr.heapify(1, comp);
        }
    }

    template <typename T, typename Func>
    static void shell_sort(vector<T>& arr, Func comp){

    }
    template <typename T, typename Func>
    static void quick_sort(vector<T>& arr, Func comp){

    }
};