#pragma once

#include<cstdlib>
#include<new>
#include<iostream>


template <typename T>
class vector{
    
public:

    explicit vector(std::size_t initial = 0){ resize(initial); }
    template <typename Func>
    explicit vector(std::size_t initial, Func generator, T min, T max, std::size_t lower, std::size_t upper){
        resize(initial);
        populate(generator,min,max,lower,upper);
    }
    ~vector(){ free(arr); }
    
    void push_back(T elem){
        if(back >= size)
            resize(growth);
            
        arr[back]=elem;
        back++;    
    }
    
    void resize(std::size_t newSize){
        if(newSize == 0){
            free(arr);
            arr = nullptr;
        }
        if(void* mem = realloc(arr, newSize * sizeof(T))){
            arr = (T*)mem;
            size = newSize;
        }else{
            throw std::bad_alloc();
        }
    }
    
    void resize(float scale){
        if(scale <= 0) {
            throw std::invalid_argument("Err: scale must be positive");
        }
        std::size_t newSize = static_cast<unsigned>(size*scale);
        resize(newSize);
    }
    
    void swap(unsigned pos1, unsigned pos2){
        
        if(pos1 >= size || pos2 >= size){
            throw std::invalid_argument("Err: attempting to swap elements outside vector boundary\n");
        }
            
        T temp = arr[pos1];
        arr[pos1] = arr[pos2];
        arr[pos2] = temp;
    }
    
    template <typename Func>
    void populate(Func generator, T min, T max,  std::size_t lower, std::size_t upper){
        
        if(lower > upper or lower >= size or upper > size){
            throw std::invalid_argument("Err: invalid populate bounds\n");
        }
        
        for(std::size_t i = lower; i<upper; i++){
            arr[i] = generator(min, max);
        }
    }
    
    void copy_to(vector<T>& dest){
        if(dest.len() < size)
            dest.resize(size);
        
        for(std::size_t i = 0; i<size; i++)
            dest[i] = arr[i];
    }

    void print(){
        for (std::size_t i = 0; i < size; i++){
            std::cout<<arr[i]<< " ";
        }
        std::cout<<'\n';
    }
    
    [[nodiscard]] std::size_t len() const { return size; }
    
    T& operator[](std::size_t n){ return arr[n]; }
    T operator[](std::size_t n) const { return arr[n]; }
    
    T* arr = nullptr;
    
    
private:    
    std::size_t size = 0;
    unsigned back = 0;
    const float growth = 1.6;
    
};