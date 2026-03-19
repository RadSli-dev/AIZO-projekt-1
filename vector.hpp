#include<cstdlib>
#include<new>
#include<iostream>
//#define NDEBUG
#include <cassert>
#define assertm(exp, msg) assert((void(msg), exp))


template <typename T>
class vector{
    
public:

    explicit vector(std::size_t initial = 0){ resize(initial); }
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
        
        if(newSize<size && newSize>back){
            std::cerr<<"Warn: attempting to shrink container below last element position!\n";
            back = newSize+1;
        }
        
        if(void* mem = realloc(arr, newSize)){
            arr = (T*)mem;
            size = newSize;
        }else{
            throw std::bad_alloc();
        }
    }
    
    inline void resize(float scale){
        std::size_t newSize = static_cast<unsigned>(size*scale);
        resize(newSize);
    }
    
    void swap(unsigned pos1, unsigned pos2){
        
        assertm(pos1 > size or pos2 > size, "Failed");
        if(pos1 > size or pos2 > size){
            std::cerr<<"Err: attempting to swap elements outside vector boundry\n";
            exit(-1);
        }else if(pos1 == pos2)
            return;
            
        T temp = arr[pos1];
        arr[pos1] = arr[pos2];
        arr[pos2] = temp;
    }
    
    template <typename Func>
    void populate(Func generator, std::size_t lower, std::size_t upper){
        
        if(lower>upper or lower > size or upper > size){
            std::cerr<<"Error: invalid populate bounds\n";
            exit(-1);
        }
        
        for(std::size_t i = lower; i<upper; i++){
            arr[i] = generator();
        }
    }
    
    void copy_to(vector<T>& dest){
        if(dest.len() < size)
            dest.resize(size);
        
        for(std::size_t i = 0; i<size; i++)
            dest[i] = arr[i];
    }
    
    std::size_t len() {return size;}
    
    T& operator[](std::size_t n){return arr[n];}
    T operator[](std::size_t n) const {return arr[n];}
    
    T* arr = nullptr;
    
    
private:    
    size_t size = 0;
    unsigned back = 0;
    const float growth = 1.6;
    
};