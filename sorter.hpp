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

    template <typename T>
    static void insertion_sort(vector<T>& arr){
        for (int i = 1; i < arr.len(); i++){
            int j = i;
            while (j > 0 && arr[j-1] > arr[j]){
                arr.swap(j,j-1);
                --j;
            }
        }
    }

    template <typename T>
    static void gapped_insertion_sort(vector<T>& arr, const std::size_t gap){
       // std::cout<< "gap:" << gap<<'\n';
        for (std::size_t i = 0; i <= gap-1; i++){
           // std::cout << i << '\n';
            for (std::size_t j = i + gap; j < arr.len(); j+=gap){
                std::size_t k = j;
               // std::cout << "    " << j << '\n';
                while (k > i && arr[k-gap] > arr[k]){
                   // std::cout <<"        " << k << " " << k-gap << '\n';
                    arr.swap(k,k-gap);
                    k-=gap;
                }
            }

        }
    }

    template <typename T>
    static void shell_sort(vector<T>& arr){
        vector<T> gaps = {3888, 3456, 3072, 2916, 2592, 2304, 2187, 2048, 1944, 1728, 1536, 1458, 1296, 1152, 1024, 972,
            864, 768, 729, 648, 576, 512, 486, 432, 384, 324, 288, 256, 243, 216, 192, 162, 144, 128, 108, 96, 81, 72, 64,
            54, 48, 36, 32, 27, 24, 18, 16, 12, 9, 8, 6, 4, 3, 2, 1};
        for (int gapi = 0; gapi < gaps.len(); gapi++){
            if (gaps[gapi] < arr.len()){
                gapped_insertion_sort(arr,gaps[gapi]);
            }
        }
    }
    template <typename T, typename Func>
    static void quick_sort(vector<T>& arr, std::size_t left, std::size_t right, Func pivot_select){
        //Correct bound check and default recursion case
        /*if (left >= arr.len() || right >= arr.len())
            throw std::invalid_argument("Err: quick_sort bounds are outside vector boundary");
        if (right-left <= 10){
            for (std::size_t i = left+1; i <= right; i++){
                std::size_t j = i;
                while (j > 0 && arr[j-1] > arr[j]){
                    arr.swap(j,j-1);
                    --j;
                }
            }
            return;
        }*/
        if(left == right)
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
