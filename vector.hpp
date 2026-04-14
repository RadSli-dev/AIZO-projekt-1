#pragma once

#include<cstdlib>
#include<new>
#include<iostream>
#include<fstream>
#include<initializer_list>

template <typename T>
class vector{
    
public:

    explicit vector(std::size_t initial = 0){ resize(initial); }
    template <typename Func>
    explicit vector(std::size_t initial, Func generator, T min, T max, std::size_t lower, std::size_t upper){
        resize(initial);
        populate(generator,min,max,lower,upper);
    }
    explicit vector(const std::string& filename) { file_import(filename); }
    vector(std::initializer_list<T> init){
        resize(init.size());
        for (T t : init){
            push_back(t);
        }
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
            arr = static_cast<T*>(mem);
            size = newSize;
        }else{
            throw std::bad_alloc();
        }
    }
    
    void resize(const float scale){
        if(scale <= 0) {
            throw std::invalid_argument("Err: scale must be positive");
        }
        const std::size_t newSize = static_cast<unsigned>(size*scale);
        resize(newSize);
    }
    
    void swap(unsigned pos1, unsigned pos2){
        
        if(pos1 >= size || pos2 >= size){
            throw std::invalid_argument("Err: attempting to swap elements outside vector boundary:\n");
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
        this->back = upper;
    }
    
    void file_import(const std::string& filename){
        std::ifstream file(filename);
        if (!file){
            throw std::invalid_argument("Err: could not open file");
        }
        int len;
        file >> len;
        if (len > size)
            resize(len);
        for (std::size_t i = 0; i < len; i++){
            file >> arr[i];
        }
        file.close();

    }

    void file_export(const std::string& filename)
    {
        std::ofstream file(filename);
        if (!file){
            throw std::invalid_argument("Err: could not open file");
        }
        file << size <<'\n';
        for (std::size_t i = 0; i < back; i++)
        {
            file << arr[i] << '\n';
        }
        file.close();
    }

    void copy_to(vector<T>& dest){
        if(dest.len() < size)
            dest.resize(size);
        dest.set_last(back);    
        for(std::size_t i = 0; i<back; i++)
            dest[i] = arr[i];
    }

    void print(){
        print(0, back);
    }

    void print(std::size_t left, std::size_t right){
        if(right > back || left > right || left > back)
            throw std::invalid_argument("Err: invalid print bounds");
        for (std::size_t i = left; i<right; i++){
            std::cout<<arr[i]<<" ";
        }
        std::cout<<'\n';
    }
    
    [[nodiscard]] std::size_t len() const { return size; }
    [[nodiscard]] std::size_t last() const { return back; }
    void set_last(std::size_t l) { this->back = l; }
    
    T& operator[](std::size_t n){ return arr[n]; }
    T operator[](std::size_t n) const { return arr[n]; }
    
    T* arr = nullptr;
    
    
private:    
    std::size_t size = 0;
    std::size_t back = 0;
    const float growth = 1.6;
    
};