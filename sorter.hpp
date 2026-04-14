#pragma once
#include "vector.hpp"
#include "heap.hpp"
#include <thread>

class sorter{
public:
    //comp ma zwracać odpowiedź na zapytanie o pierwszy argument względem drugiego -> jeżeli chcemy zapytać o to czy l > r to comp(l,r) powinien zwracać true
    template <typename T, typename Func>
    static void heap_sort(vector<T>& arr, Func comp){
        heap::build_heap(arr, comp);
        int heapSize = arr.last();
        for (int i = heapSize-1; i > 0; --i){
            arr.swap(i,0);
            --heapSize;
            heap::heapify(heapSize, 0, arr, comp);
        }
    }

    template <typename T>
    static void insertion_sort(vector<T>& arr){
        for (int i = 1; i < arr.len(); i++){
            T key = arr[i];
            int j = i;
            while (j > 0 && arr[j-1] > key){
                arr[j]  = arr[j-1];
                --j;
            }
            arr[j] = key;
        }
    }

    template <typename T>
    static void gapped_insertion_sort(vector<T>& arr, const int gap){
        /*for (int i = 0; i <= gap-1; i++){
            for (int j = i + gap; j < arr.last(); j+=gap){
                int k = j;
                while (k > i && arr[k-gap] > arr[k]){
                    arr.swap(k,k-gap);
                    k-=gap;
                }
            }

        }*/

        for (int j = gap; j < arr.len(); j++) {
            T key = arr[j];
            int k = j;

            // Shift elements instead of swapping them (1 operation vs 3)
            while (k >= gap && arr[k-gap] > key) {
                arr[k] = arr[k-gap];
                k -= gap;
            }
            arr[k] = key;
        }

    }

    template <typename T>
    static void shell_sort(vector<T>& arr, vector<int>& gaps){
        /*vector<int> gaps = {3888, 3456, 3072, 2916, 2592, 2304, 2187, 2048, 1944, 1728, 1536, 1458, 1296, 1152, 1024, 972,
            864, 768, 729, 648, 576, 512, 486, 432, 384, 324, 288, 256, 243, 216, 192, 162, 144, 128, 108, 96, 81, 72, 64,
            54, 48, 36, 32, 27, 24, 18, 16, 12, 9, 8, 6, 4, 3, 2, 1};*/
        for (int gapi = 0; gapi < gaps.last(); gapi++){
            if (gaps[gapi] < arr.len()){
                gapped_insertion_sort(arr,gaps[gapi]);
            }
        }
    }
    template <typename T, typename Func>
    static void quick_sort(vector<T>& arr, int left, int right, Func pivot_select){
        if(left >= right)
            return;
        if (right-left <= 42){
            for (int i = left+1; i <= right; i++){
                T key = arr[i];
                int j = i;
                while (j > left && arr[j-1] > key){
                    arr[j] = arr[j-1];
                    --j;
                }
                arr[j] = key;
            }
            return;
        }


        //pivot selection
        int pivot_index = pivot_select(arr, left, right);
        pivot_index = sorter::partition(arr, left, right, pivot_index);

        //recursive quick_sort call guarded by if statements to ensure correct bounds
        if (pivot_index > left){
            quick_sort(arr, left, pivot_index, pivot_select);
        }
        if (pivot_index + 1 < right){
            quick_sort(arr, pivot_index + 1, right, pivot_select);
        }
    }

    template <typename T>
    static int partition(vector<T>& arr, int left, int right, int pivot_index){
        //keep pivot safe from swaps and store it at the end of the vector
        arr.swap(pivot_index, left);
        T pivot = arr[left];
        int i = left - 1;
        int j = right + 1;
        while(true){
            do{ i++; } while(arr[i] < pivot);
            do{ j--; } while(arr[j] > pivot);

            if (i >= j) return j;
            arr.swap(i, j);
        }

        /*
        arr.swap(pivot_index, right);

        //scan array for elements <= pivot and put them on the left side of the vector.
        //store_index keeps the bounds of the left side
        int store_index = left;
        for (int i = left; i < right; ++i){
            if (arr[i] <= pivot){
                arr.swap(i, store_index);
                ++store_index;
            }
        }

        //put pivot back into correct place
        arr.swap(store_index, right);
        //arr.print(left, right);
        return store_index;
        */
    }

};
