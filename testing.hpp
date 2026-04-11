#pragma once
#include "sorter.hpp"
#include "randomizer.hpp"
#include <chrono>
#include <limits>
#include <string>

typedef struct{
    std::chrono::duration<double> times[7];
    std::string test_info;
}test_result;

void print_test(test_result t){
    std::cout<<"==================\n";
    std::cout<<t.test_info<<"\n";
    for(int i =0; i < 7; i++)
        std::cout<<t.times[i]<<'\n';
    std::cout<<"==================\n";    
}


template <typename T>
void test_insert(T x){
    randomizer rand;
    auto randT = [&rand](T min, T max){ return rand.randT(min, max); };
    test_result t;
    t.test_info = "insertion sort test of sizes 10000*2^k for k in <1,7> for random numbers of type: ";
    t.test_info = std::format("{} {}", t.test_info, typeid(T).name());
    test_result avg;
    
    for(std::size_t s = 0; s<7; s++){
        std::cout<<s;
        vector<T> data((1<<s)*10000);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, s*10000);
        const auto start_insertion{std::chrono::steady_clock::now()};
        sorter::insertion_sort(data);
        const auto finish_insertion{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_insertion{finish_insertion - start_insertion};
        t.times[s] = elapsed_insertion;
    }
    print_test(t);
}

template <typename T>
void test_shell(T t){
    
}

template <typename T>
void test_quick(T t){
    
}

template <typename T>
void test_heap(T t){
    
}