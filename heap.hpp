#pragma once
#include "vector.hpp"

template <typename T>
class heap{

public:
    explicit heap(std::size_t size){
        arr.resize(size); //creates an empty heap of size n
        heapSize = size;
    }
    template <typename Func>
    heap(vector<T>& arr, Func comp){
        arr.copy_to(this->arr);
        build_heap(comp); //creates a heap out of passed vector
    }

    //comp odpowiadający na pytanie a>b buduje max-heap, a na a<b buduje min-heap
    template <typename Func>
    void heapify(std::size_t i, Func comp){
        std::size_t largest = i;
        std::size_t left = left_index(i);
        std::size_t right = right_index(i);

        if (left < heapSize and comp(arr[left], arr[i]))
            largest = left;
        if (right < heapSize and comp(arr[right], arr[largest]))
            largest = right;
            
        
        if (largest != i){
            arr.swap(i, largest);
            heapify(largest, comp);
        }
    }

    template <typename Func>
    void build_heap(Func comp){
        heapSize = arr.last();
        for (std::size_t i = arr.last()/2; i > 0; --i){
            heapify(i, comp);
        }
        heapify(0, comp);
    }

    void swap(std::size_t i, std::size_t j) { arr.swap(i,j); }

    T parent(const std::size_t i) const { return arr[(i-1)/2]; }
    T left(const std::size_t i) const { return arr[2*i+1]; }
    T right(const std::size_t i) const { return arr[2*i+2]; }

    [[nodiscard]] static std::size_t parent_index(const std::size_t i) { return (i-1)/2; }
    [[nodiscard]] static std::size_t left_index(const std::size_t i) { return 2*i+1; }
    [[nodiscard]] static std::size_t right_index(const std::size_t i) { return 2*i+2; }

    T& operator[](std::size_t i){ return arr[i]; }
    T operator[](std::size_t i) const { return arr[i]; }

    std::size_t heapSize;
    vector<T> arr;
};