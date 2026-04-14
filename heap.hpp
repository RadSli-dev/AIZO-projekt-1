#pragma once
#include "vector.hpp"

class heap{

public:
    //comp odpowiadający na pytanie a>b buduje max-heap, a na a<b buduje min-heap
    template <typename T, typename Func>
    static void heapify(int heapSize, int i, vector<T>& arr, Func comp){
        int largest = i;
        int left = left_index(i);
        int right = right_index(i);

        if (left < heapSize and comp(arr[left], arr[i]))
            largest = left;
        if (right < heapSize and comp(arr[right], arr[largest]))
            largest = right;
            
        if (largest != i){
            arr.swap(i, largest);
            heapify(heapSize, largest, arr, comp);
        }
    }

    template <typename T, typename Func>
    static void build_heap(vector<T>& arr, Func comp){
        int heapSize = arr.last();
        for (int i = arr.last()/2; i > 0; --i){
            heapify(heapSize, i, arr, comp);
        }
        heapify(heapSize, 0, arr, comp);
    }

    //void swap(int i, int j) { arr.swap(i,j); }

    //T parent(const int i) const { return arr[(i-1)/2]; }
    //T left(const int i) const { return arr[2*i+1]; }
    //T right(const int i) const { return arr[2*i+2]; }

    [[nodiscard]] static int parent_index(const int i) { return (i-1)/2; }
    [[nodiscard]] static int left_index(const int i) { return 2*i+1; }
    [[nodiscard]] static int right_index(const int i) { return 2*i+2; }

    //T& operator[](int i){ return arr[i]; }
    //T operator[](int i) const { return arr[i]; }

    //int heapSize;
    //vector<T> arr;
};
