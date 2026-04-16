#pragma once
#include "vector.hpp"

class heap{

public:
    template <typename T>
    static void heapify(int heapSize, int i, vector<T>& arr){
        int largest = i;
        int left = left_index(i);
        int right = right_index(i);

        if (left < heapSize and arr[left] > arr[i])
            largest = left;
        if (right < heapSize and arr[right] > arr[largest])
            largest = right;
            
        if (largest != i){
            arr.swap(i, largest);
            heapify(heapSize, largest, arr);
        }
    }

    template <typename T>
    static void build_heap(vector<T>& arr){
        int heapSize = arr.last();
        for (int i = arr.last()/2; i > 0; --i){
            heapify(heapSize, i, arr);
        }
        heapify(heapSize, 0, arr);
    }

    [[nodiscard]] static int parent_index(const int i) { return (i-1)/2; }
    [[nodiscard]] static int left_index(const int i) { return 2*i+1; }
    [[nodiscard]] static int right_index(const int i) { return 2*i+2; }
};
