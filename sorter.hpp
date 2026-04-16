#pragma once
#include "vector.hpp"
#include "heap.hpp"

class sorter{
public:
    //comp ma zwracać odpowiedź na zapytanie o pierwszy argument względem drugiego -> jeżeli chcemy zapytać o to czy l > r to comp(l,r) powinien zwracać true
    template <typename T>
    static void heap_sort(vector<T>& arr){
        heap::build_heap<T>(arr);
        int heapSize = arr.last();
        for (int i = heapSize-1; i > 0; --i){
            arr.swap(i,0);
            --heapSize;
            heap::heapify(heapSize, 0, arr);
        }
    }

    template <typename T>
    static void insertion_sort(vector<T>& arr){
        for (int i = 1; i < arr.last(); i++){
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
        for (int j = gap; j < arr.last(); j++) {
            T key = arr[j];
            int k = j;
            while (k >= gap && arr[k-gap] > key) {
                arr[k] = arr[k-gap];
                k -= gap;
            }
            arr[k] = key;
        }

    }

    template <typename T>
    static void shell_sort(vector<T>& arr, const vector<int>& gaps){
        for (int gapi = 0; gapi < gaps.last(); gapi++){
            if (gaps[gapi] < arr.len()){
                gapped_insertion_sort(arr,gaps[gapi]);
            }
        }
    }

    template <typename T, typename Func>
    static void quick_sort_desc(vector<T>& arr, int left, int right, Func pivot_select){
        if(left >= right)
            return;
        if (right-left <= 42){
            for (int i = left; i <= right; i++){
                T key = arr[i];
                int j = i;
                while (j > left && arr[j-1] < key){
                    arr[j] = arr[j-1];
                    --j;
                }
                arr[j] = key;
            }
            return;
        }


        //pivot selection
        int pivot_index = pivot_select(left, right);
        pivot_index = sorter::partition_desc(arr, left, right, pivot_index);
        //recursive quick_sort call guarded by if statements to ensure correct bounds
        if (pivot_index > left){
            quick_sort_desc(arr, left, pivot_index, pivot_select);
        }
        if (pivot_index + 1 <= right){
            quick_sort_desc(arr, pivot_index + 1, right, pivot_select);
        }
    }

    template <typename T>
    static int partition_desc(vector<T>& arr, int left, int right, int pivot_index){
        T pivot = arr[pivot_index];
        arr.swap(pivot_index, left);
        int i = left - 1;
        int j = right + 1;
        while(true){
            do{ i++; } while(arr[i] > pivot);
            do{ j--; } while(arr[j] < pivot);

            if (i >= j) return j;
            arr.swap(i, j);
        }
    }

    template <typename T, typename Func>
    static void quick_sort(vector<T>& arr, int left, int right, Func pivot_select){
        if(left >= right)
            return;
        if (right-left <= 5){
            for (int i = left; i <= right; i++){
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
        int pivot_index = pivot_select(left, right);
        pivot_index = sorter::partition(arr, left, right, pivot_index);
        //recursive quick_sort call guarded by if statements to ensure correct bounds
        if (pivot_index > left){
            quick_sort(arr, left, pivot_index, pivot_select);
        }
        if (pivot_index + 1 <= right){
            quick_sort(arr, pivot_index + 1, right, pivot_select);
        }
    }

    template <typename T>
    static int partition(vector<T>& arr, int left, int right, int pivot_index){
        T pivot = arr[pivot_index];
        arr.swap(pivot_index, left);
        int i = left - 1;
        int j = right + 1;
        while(true){
            do{ i++; } while(arr[i] < pivot);
            do{ j--; } while(arr[j] > pivot);

            if (i >= j) return j;
            arr.swap(i, j);
        }
    }

};
