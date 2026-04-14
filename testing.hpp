#pragma once
#include "sorter.hpp"
#include "randomizer.hpp"
#include <chrono>
#include <limits>
#include <string>

class test_result{
public:
    void print_test(){
    std::cout<<"==================\n";
    std::cout<<test_info<<"\n";
    for(auto time : times)
        std::cout<<time<<'\n';
    std::cout<<"==================\n";    
    }
    
    void operator+=(test_result& t){
        for(int i = 0; i < 7; i++)
            times[i] += t.times[i];
    }    
    
    template <typename T>
    void operator/=(T t){
        for(int i = 0; i < 7; i++)
            times[i] /= t;
    }
    
    std::chrono::duration<double> times[7]{};
    std::string test_info;
};


template <typename T>
static inline void check_correct_sorting(vector<T>& arr){
    bool sorted_nonasc = true, sorted_nondesc = true;
    for (int i = 1; i < arr.last(); i++){
        if (arr[i] > arr[i-1])
            sorted_nonasc = false;
        if (arr[i] < arr[i-1])
            sorted_nondesc = false;
    }
    std::cout << sorted_nonasc << " " << sorted_nondesc <<'\n';
}


template <typename T>
void test_insert(T x, int baseSize, int iterations){
    randomizer rand;
    auto randT = [&rand](T min, T max){ return rand.randT(min, max); };
    test_result t;
    t.test_info = "insertion sort test of sizes 1000*2^k for k in <1,7> for random numbers of type: ";
    t.test_info = std::format("{} {}", t.test_info, typeid(T).name());
    test_result avg;
    avg.test_info = "averaged insertion sort test of sizes 1000*2^k for k in <1,7> for random numbers of type: ";
    avg.test_info = std::format("{} {}", avg.test_info, typeid(T).name());
    
    for(int s = 1; s<=7; ++s){
        vector<T> data((1<<s)*baseSize);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize);
        auto start_insertion{std::chrono::steady_clock::now()};
        sorter::insertion_sort(data);
        auto finish_insertion{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_insertion{finish_insertion - start_insertion};
        t.times[s-1] = elapsed_insertion;
        check_correct_sorting(data);
    }
    t.print_test();
    
    for(int i = 0; i < iterations; i++){
        for(int s = 1; s<=7; ++s){
        vector<T> data((1<<s)*baseSize);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize);
        auto start_insertion{std::chrono::steady_clock::now()};
        sorter::insertion_sort(data);
        auto finish_insertion{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_insertion{finish_insertion - start_insertion};
        avg.times[s-1] += elapsed_insertion;
        //check_correct_sorting(data);
        }
    }
    avg /= iterations;
    avg.print_test();
}

template <typename T>
void test_shell(T x, int baseSize, int iterations){
    randomizer rand;
    auto randT = [&rand](T min, T max){ return rand.randT(min, max); };
    //vector<int> gaps = {
    //    3888, 3456, 3072, 2916, 2592, 2304, 2187, 2048, 1944, 1728, 1536, 1458, 1296, 1152, 1024, 972,
    //    864, 768, 729, 648, 576, 512, 486, 432, 384, 324, 288, 256, 243, 216, 192, 162, 144, 128, 108, 96, 81, 72, 64,
    //    54, 48, 36, 32, 27, 24, 18, 16, 12, 9, 8, 6, 4, 3, 2, 1
    //};                                                              //Pratt 1971
    //vector<int> gaps = {1750, 701, 301, 132, 57, 23, 10, 4, 1};       //Ciura 2001
    //vector<int> gaps = {9841, 3280, 1093, 364, 121, 40, 13, 4, 1};  //Knuth 1973
    vector<int> gaps = {65921, 16577, 4193, 1073, 281, 77, 23, 8, 1}; //Sedgewick 1982 O(N^(4/3)
    //vector<int> gaps = {8191, 4095, 2047, 1023, 511, 255, 127, 63, 31, 15, 7, 3, 1, 0}; //Hibbard 1963 O(N^(3/2));
    //vector<int> gaps = {36289, 16001, 8929, 3905, 2161, 929, 505, 209, 109, 41, 19, 5, 1}; //Sedgewick 1986 O(N^(4/3)
    test_result t;
    t.test_info = "shell sort test of sizes 1000*2^k for k in <1,7> for random numbers of type: ";
    t.test_info = std::format("{} {}", t.test_info, typeid(T).name());
    test_result avg;
    avg.test_info = "averaged shell sort test of sizes 1000*2^k for k in <1,7> for random numbers of type: ";
    avg.test_info = std::format("{} {}", avg.test_info, typeid(T).name());

    for(int s = 1; s<=7; ++s){
        vector<T> data((1<<s)*baseSize);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize);
        auto start_insertion{std::chrono::steady_clock::now()};
        sorter::shell_sort(data, gaps);
        auto finish_insertion{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_insertion{finish_insertion - start_insertion};
        t.times[s-1] = elapsed_insertion;
        check_correct_sorting(data);
    }
    t.print_test();

    for(int i = 0; i < iterations; i++){
        for(int s = 1; s<=7; ++s){
            vector<T> data((1<<s)*baseSize);
            data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize);
            auto start_insertion{std::chrono::steady_clock::now()};
            sorter::shell_sort(data, gaps);
            auto finish_insertion{std::chrono::steady_clock::now()};
            const std::chrono::duration<double> elapsed_insertion{finish_insertion - start_insertion};
            avg.times[s-1] += elapsed_insertion;
            //check_correct_sorting(data);
        }
    }
    avg /= iterations;
    avg.print_test();
}

template <typename T>
void test_quick(T x, int baseSize, int iterations){
    randomizer rand;
    auto randT = [&rand](T min, T max){ return rand.randT(min, max); };
    auto pivot_s = [](vector<T>& arr, int left, int right){return right;};

    test_result t;
    t.test_info = "quick sort test of sizes 100000*2^k for k in <1,7> with pivot always right for random numbers of type: ";
    t.test_info = std::format("{} {}", t.test_info, typeid(T).name());
    test_result avg;
    avg.test_info = "averaged quick sort test of sizes 100000*2^k for k in <1,7> with pivot always right for random numbers of type: ";
    avg.test_info = std::format("{} {}", avg.test_info, typeid(T).name());
    
    for(int s = 1; s<=7; ++s){
        vector<T> data((1<<s)*baseSize);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize);
        auto start_quick{std::chrono::steady_clock::now()};
        sorter::quick_sort(data, 0, (1<<s)*baseSize - 1, pivot_s);
        auto finish_quick{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_quick{finish_quick - start_quick};
        t.times[s-1] = elapsed_quick;
        check_correct_sorting(data);
    }
    t.print_test();
    
    for(int i = 0; i < iterations; i++){
        for(int s = 1; s<=7; ++s){
        vector<T> data((1<<s)*baseSize);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize);
        auto start_quick{std::chrono::steady_clock::now()};
        sorter::quick_sort(data, 0, (1<<s)*baseSize - 1, pivot_s);
        auto finish_quick{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_quick{finish_quick - start_quick};
        avg.times[s-1] += elapsed_quick;
        //check_correct_sorting(data);
        }
    }    
    avg /= iterations;
    avg.print_test();
}

template <typename T>
void test_heap(T x, int baseSize, int iterations){
    randomizer rand;
    auto randT = [&rand](T min, T max){ return rand.randT(min, max); };
    auto comp_s = [](T a, T b){return a < b;};
    
    test_result t;
    t.test_info = "heap sort test of sizes 100000*2^k for k in <1,7> for random numbers of type: ";
    t.test_info = std::format("{} {}", t.test_info, typeid(T).name());
    test_result avg;
    avg.test_info = "averaged heap sort test of sizes 100000*2^k for k in <1,7> for random numbers of type: ";
    avg.test_info = std::format("{} {}", avg.test_info, typeid(T).name());
    
    for(int s = 1; s<=7; ++s){
        vector<T> data((1<<s)*baseSize);
        data.populate(randT, std::numeric_limits<T>::min()*0, 10.f/*std::numeric_limits<T>::max()*/, 0, (1<<s)*baseSize);
        auto start_quick{std::chrono::steady_clock::now()};
        sorter::heap_sort(data, comp_s);
        auto finish_quick{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_quick{finish_quick - start_quick};
        t.times[s-1] = elapsed_quick;
        check_correct_sorting(data);
    }
    t.print_test();
    
    for(int i = 0; i < iterations; i++){
        for(int s = 1; s<=7; ++s){
        vector<T> data((1<<s)*baseSize);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize);
        auto start_quick{std::chrono::steady_clock::now()};
        sorter::heap_sort(data, comp_s);
        auto finish_quick{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_quick{finish_quick - start_quick};
        avg.times[s-1] += elapsed_quick;
        //check_correct_sorting(data);
        }
    }    
    avg /= iterations;
    avg.print_test();
    
}
