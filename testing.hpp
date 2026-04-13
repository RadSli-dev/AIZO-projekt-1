#pragma once
#include "sorter.hpp"
#include "randomizer.hpp"
#include <chrono>
#include <limits>
#include <string>

typedef struct{
    std::chrono::duration<double> times[7]{};
    std::string test_info;
}test_result;

static inline void print_test(const test_result& t){
    std::cout<<"==================\n";
    std::cout<<t.test_info<<"\n";
    for(auto time : t.times)
        std::cout<<time<<'\n';
    std::cout<<"==================\n";    
}
template <typename T>
static inline void check_correct_sorting(vector<T>& arr){
    bool sorted_nonasc = true, sorted_nondesc = true;
    for (std::size_t i = 1; i < arr.last(); i++){
        if (arr[i] > arr[i-1])
            sorted_nonasc = false;
        if (arr[i] < arr[i-1])
            sorted_nondesc = false;
    }
    std::cout << sorted_nonasc << " " << sorted_nondesc <<'\n';
}


template <typename T>
void test_insert(T x){
    randomizer rand;
    auto randT = [&rand](T min, T max){ return rand.randT(min, max); };
    test_result t;
    t.test_info = "insertion sort test of sizes 10000*2^k for k in <1,7> for random numbers of type: ";
    t.test_info = std::format("{} {}", t.test_info, typeid(T).name());
    test_result avg;
    std::size_t baseSize = 10000;
    for(std::size_t s = 1; s<=7; ++s){
        vector<T> data((1<<s)*baseSize);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize);
        auto start_insertion{std::chrono::steady_clock::now()};
        sorter::insertion_sort(data);
        auto finish_insertion{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_insertion{finish_insertion - start_insertion};
        t.times[s-1] = elapsed_insertion;
        check_correct_sorting(data);
    }
    print_test(t);
}

template <typename T>
void test_shell(T x){
    
}

template <typename T>
void test_quick(T x){
    randomizer rand;
    auto randT = [&rand](T min, T max){ return rand.randT(min, max); };
    auto pivot_s = [](vector<T>& arr, std::size_t left, std::size_t right){return right;};

    test_result t;
    t.test_info = "quick sort test of sizes 100000*2^k for k in <1,7> with pivot always right for random numbers of type: ";
    t.test_info = std::format("{} {}", t.test_info, typeid(T).name());
    test_result avg;
    std::size_t baseSize = 10000;
    for(std::size_t s = 1; s<=7; ++s){
        vector<T> data((1<<s)*baseSize);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize);
        auto start_quick{std::chrono::steady_clock::now()};
        sorter::quick_sort(data, 0, (1<<s)*baseSize - 1, pivot_s);
        auto finish_quick{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_quick{finish_quick - start_quick};
        t.times[s-1] = elapsed_quick;
        check_correct_sorting(data);
    }
    print_test(t);
}

template <typename T>
void test_heap(T x){
    
}