#pragma once

#include<iostream>
#include<fstream>
#include<initializer_list>

template <typename T>
class vector{
    
public:

    explicit vector(const int initial = 1){ resize(initial); }
    template <typename Func>
    explicit vector(const int initial, Func generator, T min, T max, int lower, int upper){
        resize(initial);
        populate(generator,min,max,lower,upper);
    }
    explicit vector(const std::string& filename) { file_import(filename); }
    vector(std::initializer_list<T> init){
        resize(static_cast<int>(init.size()));
        for (T t : init){
            push_back(t);
        }
    }
    vector(const vector& v) {
        size = v.size;
        back = v.back;
        arr = new T[size];
        for (int i = 0; i < back; ++i) {
            arr[i] = v.arr[i];
        }
    }
    ~vector(){ delete[] arr; }
    
    void push_back(const T& elem){
        if(back >= size)
            resize(growth);
            
        arr[back]=elem;
        back++;    
    }
    
    void resize(int newSize){
        if(newSize == 0){
            delete[] arr;
            arr = nullptr;
            size = 0;
            back = 0;
            return;
        }

        T* newArr = new T[newSize];
        if(arr != nullptr){
            int elementsToCopy = (back < newSize) ? back : newSize;
            for(int i = 0; i < elementsToCopy; i++)
                newArr[i] = std::move(arr[i]);
            delete[] arr;
        }

        arr = newArr;
        size = newSize;
        back = (back > size) ? size : back;
    }
    
    void resize(const float scale){
        if(scale <= 1.0f) {
            throw std::invalid_argument("Err: scale must be strictly greater than 1 for growth");
        }
        if (size == 0) {
            resize(static_cast<int>(2));
            return;
        }

        int newSize = static_cast<int>(size * scale);
        if (newSize <= size) {
            newSize = size + 1;
        }

        resize(newSize);
    }
    
    void swap(int pos1, int pos2){
        T temp = std::move(arr[pos1]);
        arr[pos1] = std::move(arr[pos2]);
        arr[pos2] = std::move(temp);
    }
    
    template <typename Func>
    void populate(Func generator, T min, T max,  int lower, int upper){
        
        if(lower > upper or lower >= size or upper > size){
            throw std::invalid_argument("Err: invalid populate bounds\n");
        }
        for(int i = lower; i<upper; i++){
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
        for (int i = 0; i < len; i++){
            file >> arr[i];
        }
        back = len;
        file.close();

    }

    void file_export(const std::string& filename){
        std::ofstream file(filename);
        if (!file){
            throw std::invalid_argument("Err: could not open file");
        }
        file << size <<'\n';
        for (int i = 0; i < back; i++)
        {
            file << arr[i] << '\n';
        }
        file.close();
    }

    void copy_to(vector<T>& dest){
        if(dest.len() < size)
            dest.resize(size);
        dest.set_last(back);    
        for(int i = 0; i<back; i++)
            dest[i] = arr[i];
    }

    void print(){
        print(0, back);
    }

    void print(int left, int right){
        if(right > back || left > right || left > back)
            throw std::invalid_argument("Err: invalid print bounds");
        for (int i = left; i<right; i++){
            std::cout<<arr[i]<<" ";
        }
        std::cout<<'\n';
    }
    
    [[nodiscard]] int len() const { return size; }
    [[nodiscard]] int last() const { return back; }
    void set_last(int l) { this->back = l; }
    
    T& operator[](int n){ return arr[n]; }
    T operator[](int n) const { return arr[n]; }
    
    T* arr = nullptr;
    
    
private:    
    int size = 0;
    int back = 0;
    const float growth = 2.f;
    
};
