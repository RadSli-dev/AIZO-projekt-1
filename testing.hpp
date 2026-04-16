#pragma once
#include "sorter.hpp"
#include "randomizer.hpp"
#include <chrono>
#include <functional>
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
    
    void operator+=(const test_result& t){
        for(int i = 0; i < 7; i++)
            times[i] += t.times[i];
    }    
    
    template <typename T>
    void operator/=(T t){
        for(auto & time : times)
            time /= t;
    }

    void reset(){
        for(auto & time : times)
            time *= 0;
        test_info = "";
    }

    std::chrono::duration<double> times[7]{};
    std::string test_info;
};
template <typename T>
static void check_correct_sorting(vector<T>& arr){
    bool sorted_nonasc = true, sorted_nondesc = true;
    for (int i = 1; i < arr.last(); i++){
        if (arr[i] > arr[i-1])
            sorted_nonasc = false;
        if (arr[i] < arr[i-1])
            sorted_nondesc = false;
    }
    std::cout << sorted_nonasc << " " << sorted_nondesc <<'\n';
}


template <typename T, typename Func>
void run_insertion_test(test_result& t,  test_result& avg, const int baseSize, const int iterations, Func prepare_data){
    for(int s = 1; s<=7; ++s){
        vector<T> data((1<<s)*baseSize);
        prepare_data(data, s, baseSize);
        auto start_insertion{std::chrono::steady_clock::now()};
        sorter::insertion_sort(data);
        auto finish_insertion{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_insertion{finish_insertion - start_insertion};
        t.times[s-1] = elapsed_insertion;
        //check_correct_sorting(data);
    }
    t.print_test();
    for(int i = 0; i < iterations; i++){
        for(int s = 1; s<=7; ++s){
            vector<T> data((1<<s)*baseSize);
            prepare_data(data, s, baseSize);
            auto start_insertion{std::chrono::steady_clock::now()};
            sorter::insertion_sort(data);
            auto finish_insertion{std::chrono::steady_clock::now()};
            const std::chrono::duration<double> elapsed_insertion{finish_insertion - start_insertion};
            avg.times[s-1] += elapsed_insertion;
        }
    }
    avg /= iterations;
    avg.print_test();
}
template <typename T>
void test_insert(const int baseSize, const int iterations){
    randomizer rand;
    auto randT = [&rand](T min, T max){ return rand.randT(min, max); };
    auto zero = [](T min, T max){ return std::numeric_limits<T>::min(); };
    auto fullRandom = [&randT](vector<T>& data, const int s, const int baseSize_) { data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize_); };
    auto sorted33 = [&randT, zero](vector<T>& data, const int s, const int baseSize_){
        data.populate(zero, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, ((1<<s)*baseSize_)/3);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), ((1<<s)*baseSize_)/3, (1<<s)*baseSize_);
    };
    auto sorted67 = [&randT, zero](vector<T>& data, const int s, const int baseSize_){
        data.populate(zero, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (((1<<s)*baseSize_)*2)/3);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), (((1<<s)*baseSize_)*2)/3, (1<<s)*baseSize_);
    };
    auto sortedAsc = [&randT](vector<T>& data, const int s, const int baseSize_){
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize_);
        sorter::quick_sort(data, 0, (1<<s)*baseSize_ - 1, [](const int left, const int right) -> int { return left; });
    };
    auto sortedDesc = [&randT](vector<T>& data, const int s, const int baseSize_){
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize_);
        sorter::quick_sort_desc(data, 0, (1<<s)*baseSize_ - 1, [](const int left, const int right) -> int { return left; });
    };

    test_result t;
    test_result avg;
    t.test_info = std::format("{} {} {} {}", "insertion sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for random numbers of type: ", typeid(T).name());
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged insertion sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for random numbers of type:", typeid(T).name());
    run_insertion_test<T>(t, avg, baseSize, iterations, fullRandom);

    t.reset();
    t.test_info = std::format("{} {} {} {}", "insertion sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for 33% sorted array of random numbers of type:", typeid(T).name());
    avg.reset();
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged insertion sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for 33% sorted array of random numbers of type:", typeid(T).name());
    run_insertion_test<T>(t, avg, baseSize, iterations, sorted33);

    t.reset();
    t.test_info = std::format("{} {} {} {}", "insertion sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for 67% sorted array of random numbers of type:", typeid(T).name());
    avg.reset();
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged insertion sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for 67% sorted array of random numbers of type:", typeid(T).name());
    run_insertion_test<T>(t, avg, baseSize, iterations, sorted67);

    t.reset();
    t.test_info = std::format("{} {} {} {}", "insertion sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for sorted nondesc array of random numbers of type:", typeid(T).name());
    avg.reset();
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged insertion sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for sorted nondesc array of random numbers of type:", typeid(T).name());
    run_insertion_test<T>(t, avg, baseSize, iterations, sortedAsc);

    t.reset();
    t.test_info = std::format("{} {} {} {}", "insertion sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for sorted nonasc array of random numbers of type:", typeid(T).name());
    avg.reset();
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged insertion sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for sorted nonasc array of random numbers of type:", typeid(T).name());
    run_insertion_test<T>(t, avg, baseSize, iterations, sortedDesc);
}

template <typename T, typename Func>
void run_shell_test(test_result& t,  test_result& avg, const vector<int>* gaps, const int baseSize, const int iterations, Func prepare_data){
    for(int s = 1; s<=7; ++s){
        vector<T> data((1<<s)*baseSize);
        prepare_data(data, s, baseSize);
        auto start_insertion{std::chrono::steady_clock::now()};
        sorter::shell_sort(data, *gaps);
        auto finish_insertion{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_insertion{finish_insertion - start_insertion};
        t.times[s-1] = elapsed_insertion;
        check_correct_sorting(data);
    }
    t.print_test();
    for(int i = 0; i < iterations; i++){
        for(int s = 1; s<=7; ++s){
            vector<T> data((1<<s)*baseSize);
            prepare_data(data, s, baseSize);
            auto start_insertion{std::chrono::steady_clock::now()};
            sorter::shell_sort(data, *gaps);
            auto finish_insertion{std::chrono::steady_clock::now()};
            const std::chrono::duration<double> elapsed_insertion{finish_insertion - start_insertion};
            avg.times[s-1] += elapsed_insertion;
        }
    }
    avg /= iterations;
    avg.print_test();
}
template <typename T>
void test_shell(const int baseSize, const int iterations, const int selectedGap){
    randomizer rand;
    auto randT = [&rand](T min, T max){ return rand.randT(min, max); };
    auto zero = [](T min, T max){ return std::numeric_limits<T>::min(); };
    auto fullRandom = [&randT](vector<T>& data, const int s, const int baseSize_) { data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize_); };
    auto sorted33 = [&randT, zero](vector<T>& data, const int s, const int baseSize_){
        data.populate(zero, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, ((1<<s)*baseSize_)/3);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), ((1<<s)*baseSize_)/3, (1<<s)*baseSize_);
    };
    auto sorted67 = [&randT, zero](vector<T>& data, const int s, const int baseSize_){
        data.populate(zero, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (((1<<s)*baseSize_)*2)/3);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), (((1<<s)*baseSize_)*2)/3, (1<<s)*baseSize_);
    };
    auto sortedAsc = [&randT](vector<T>& data, const int s, const int baseSize_){
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize_);
        sorter::quick_sort(data, 0, (1<<s)*baseSize_ - 1, [](const int left, const int right) -> int { return left; });
    };
    auto sortedDesc = [&randT](vector<T>& data, const int s, const int baseSize_){
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize_);
        sorter::quick_sort_desc(data, 0, (1<<s)*baseSize_ - 1, [](const int left, const int right) -> int { return left; });
    };

    vector<int> Pratt1971 = {
        3888, 3456, 3072, 2916, 2592, 2304, 2187, 2048, 1944, 1728, 1536, 1458, 1296, 1152, 1024, 972,
        864, 768, 729, 648, 576, 512, 486, 432, 384, 324, 288, 256, 243, 216, 192, 162, 144, 128, 108, 96, 81, 72, 64,
        54, 48, 36, 32, 27, 24, 18, 16, 12, 9, 8, 6, 4, 3, 2, 1
    };                                                              //Pratt 1971
    vector<int> Ciura2001 = {1750, 701, 301, 132, 57, 23, 10, 4, 1};       //Ciura 2001
    vector<int> Knuth1973 = {9841, 3280, 1093, 364, 121, 40, 13, 4, 1};  //Knuth 1973
    vector<int> Sedgewick1982 = {65921, 16577, 4193, 1073, 281, 77, 23, 8, 1}; //Sedgewick 1982 O(N^(4/3))
    vector<int> Hibbard1963 = {65535, 32767, 16383, 8191, 4095, 2047, 1023, 511, 255, 127, 63, 31, 15, 7, 3, 1}; //Hibbard 1963 O(N^(3/2));
    vector<vector<int>*> gaps(5);
    gaps.push_back(&Pratt1971);
    gaps.push_back(&Ciura2001);
    gaps.push_back(&Knuth1973);
    gaps.push_back(&Sedgewick1982);
    gaps.push_back(&Hibbard1963);
    vector<int>* selected = gaps[selectedGap];

    test_result t;
    test_result avg;
    t.test_info = std::format("{} {} {} {}", "shell sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for random numbers of type: ", typeid(T).name());
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged shell sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for random numbers of type: ", typeid(T).name());
    run_shell_test<T>(t, avg, selected, baseSize, iterations, fullRandom);

    t.reset();
    t.test_info = std::format("{} {} {} {}", "shell sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for 33% sorted array of random numbers of type: ", typeid(T).name());
    avg.reset();
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged shell sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for 33% sorted array of random numbers of type: ", typeid(T).name());
    run_shell_test<T>(t, avg, selected, baseSize, iterations, sorted33);

    t.reset();
    t.test_info = std::format("{} {} {} {}", "shell sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for 67% sorted array of random numbers of type: ", typeid(T).name());
    avg.reset();
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged shell sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for 67% sorted array of random numbers of type: ", typeid(T).name());
    run_shell_test<T>(t, avg, selected, baseSize, iterations, sorted67);

    t.reset();
    t.test_info = std::format("{} {} {} {}", "shell sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for sorted nondesc array of random numbers of type: ", typeid(T).name());
    avg.reset();
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged shell sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for sorted nondesc array of random numbers of type: ", typeid(T).name());
    run_shell_test<T>(t, avg, selected, baseSize, iterations, sortedAsc);

    t.reset();
    t.test_info = std::format("{} {} {} {}", "shell sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for sorted nonasc array of random numbers of type: ", typeid(T).name());
    avg.reset();
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged shell sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for sorted nonasc array of random numbers of type: ", typeid(T).name());
    run_shell_test<T>(t, avg, selected, baseSize, iterations, sortedDesc);
}

template <typename T, typename Func1, typename Func2>
void run_quick_test(test_result& t,  test_result& avg, const int baseSize, const int iterations, Func1 prepare_data, Func2 pivot_select){
    for(int s = 1; s<=7; ++s){
        vector<T> data((1<<s)*baseSize);
        prepare_data(data, s, baseSize);
        auto start_insertion{std::chrono::steady_clock::now()};
        sorter::quick_sort(data, 0, (1<<s)*baseSize - 1, pivot_select);
        auto finish_insertion{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_insertion{finish_insertion - start_insertion};
        t.times[s-1] = elapsed_insertion;
        check_correct_sorting(data);
    }
    t.print_test();
    for(int i = 0; i < iterations; i++){
        for(int s = 1; s<=7; ++s){
            vector<T> data((1<<s)*baseSize);
            prepare_data(data, s, baseSize);
            auto start_insertion{std::chrono::steady_clock::now()};
            sorter::quick_sort(data, 0, (1<<s)*baseSize - 1, pivot_select);
            auto finish_insertion{std::chrono::steady_clock::now()};
            const std::chrono::duration<double> elapsed_insertion{finish_insertion - start_insertion};
            avg.times[s-1] += elapsed_insertion;
        }
    }
    avg /= iterations;
    avg.print_test();
}
template <typename T>
void test_quick(const int baseSize, const int iterations, const int selectedPivot){
    randomizer rand;
    auto randT = [&rand](T min, T max){ return rand.randT(min, max); };

    auto zero = [](T min, T max){ return std::numeric_limits<T>::min(); };
    auto fullRandom = [&randT](vector<T>& data, const int s, const int baseSize_) { data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize_); };
    auto sorted33 = [&randT, zero](vector<T>& data, const int s, const int baseSize_){
        data.populate(zero, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, ((1<<s)*baseSize_)/3);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), ((1<<s)*baseSize_)/3, (1<<s)*baseSize_);
    };
    auto sorted67 = [&randT, zero](vector<T>& data, const int s, const int baseSize_){
        data.populate(zero, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (((1<<s)*baseSize_)*2)/3);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), (((1<<s)*baseSize_)*2)/3, (1<<s)*baseSize_);
    };
    auto sortedAsc = [&randT](vector<T>& data, const int s, const int baseSize_){
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize_);
        sorter::quick_sort(data, 0, (1<<s)*baseSize_ - 1, [](const int left, const int right) -> int { return left; });
    };
    auto sortedDesc = [&randT](vector<T>& data, const int s, const int baseSize_){
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize_);
        sorter::quick_sort_desc(data, 0, (1<<s)*baseSize_ - 1, [](const int left, const int right) -> int { return left; });
    };

    auto pivot_r = [](const int left, const int right) -> int { return right; };
    auto pivot_l = [](const int left, const int right) -> int { return left; };
    auto pivot_rand = [&rand](const int left, const int right) -> int { return rand.randT(left, right); };
    auto pivot_m = [](const int left, const int right) -> int { return (left+right)/2; };

    std::function<int(int, int)> pivot_select;
    if (selectedPivot == 1)
        pivot_select = pivot_l;
    else if (selectedPivot == 2)
        pivot_select = pivot_r;
    else if (selectedPivot == 0)
        pivot_select = pivot_m;
    else
        pivot_select = pivot_rand;

    test_result t;
    test_result avg;
    t.test_info = std::format("{} {} {} {}", "quick sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for random numbers of type: ", typeid(T).name());
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged quick sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for random numbers of type:", typeid(T).name());
    run_quick_test<T>(t, avg, baseSize, iterations, fullRandom, pivot_select);

    t.reset();
    t.test_info = std::format("{} {} {} {}", "quick sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for 33% sorted array of random numbers of type:", typeid(T).name());
    avg.reset();
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged quick sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for 33% sorted array of random numbers of type:", typeid(T).name());
    run_quick_test<T>(t, avg, baseSize, iterations, sorted33, pivot_select);

    t.reset();
    t.test_info = std::format("{} {} {} {}", "quick sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for 67% sorted array of random numbers of type:", typeid(T).name());
    avg.reset();
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged quick sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for 67% sorted array of random numbers of type:", typeid(T).name());
    run_quick_test<T>(t, avg, baseSize, iterations, sorted67, pivot_select);

    t.reset();
    t.test_info = std::format("{} {} {} {}", "quick sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for sorted nondesc array of random numbers of type:", typeid(T).name());
    avg.reset();
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged quick sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for sorted nondesc array of random numbers of type:", typeid(T).name());
    run_quick_test<T>(t, avg, baseSize, iterations, sortedAsc, pivot_select);

    t.reset();
    t.test_info = std::format("{} {} {} {}", "quick sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for sorted nonasc array of random numbers of type:", typeid(T).name());
    avg.reset();
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged quick sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for sorted nonasc array of random numbers of type:", typeid(T).name());
    run_quick_test<T>(t, avg, baseSize, iterations, sortedDesc, pivot_select);
}

template <typename T, typename Func>
void run_heap_test(test_result& t,  test_result& avg, const int baseSize, const int iterations, Func prepare_data){
    for(int s = 1; s<=7; ++s){
        vector<T> data((1<<s)*baseSize);
        prepare_data(data, s, baseSize);
        auto start_insertion{std::chrono::steady_clock::now()};
        sorter::heap_sort(data);
        auto finish_insertion{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_insertion{finish_insertion - start_insertion};
        t.times[s-1] = elapsed_insertion;
        //check_correct_sorting(data);
    }
    t.print_test();
    for(int i = 0; i < iterations; i++){
        for(int s = 1; s<=7; ++s){
            vector<T> data((1<<s)*baseSize);
            prepare_data(data, s, baseSize);
            auto start_insertion{std::chrono::steady_clock::now()};
            sorter::heap_sort(data);
            auto finish_insertion{std::chrono::steady_clock::now()};
            const std::chrono::duration<double> elapsed_insertion{finish_insertion - start_insertion};
            avg.times[s-1] += elapsed_insertion;
        }
    }
    avg /= iterations;
    avg.print_test();
}
template <typename T>
void test_heap(const int baseSize, const int iterations){
    randomizer rand;
    auto randT = [&rand](T min, T max){ return rand.randT(min, max); };
    auto zero = [](T min, T max){ return std::numeric_limits<T>::min(); };
    auto fullRandom = [&randT](vector<T>& data, const int s, const int baseSize_) { data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize_); };
    auto sorted33 = [&randT, zero](vector<T>& data, const int s, const int baseSize_){
        data.populate(zero, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, ((1<<s)*baseSize_)/3);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), ((1<<s)*baseSize_)/3, (1<<s)*baseSize_);
    };
    auto sorted67 = [&randT, zero](vector<T>& data, const int s, const int baseSize_){
        data.populate(zero, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (((1<<s)*baseSize_)*2)/3);
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), (((1<<s)*baseSize_)*2)/3, (1<<s)*baseSize_);
    };
    auto sortedAsc = [&randT](vector<T>& data, const int s, const int baseSize_){
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize_);
        sorter::quick_sort(data, 0, (1<<s)*baseSize_ - 1, [](const int left, const int right) -> int { return left; });
    };
    auto sortedDesc = [&randT](vector<T>& data, const int s, const int baseSize_){
        data.populate(randT, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), 0, (1<<s)*baseSize_);
        sorter::quick_sort_desc(data, 0, (1<<s)*baseSize_ - 1, [](const int left, const int right) -> int { return left; });
    };

    test_result t;
    test_result avg;
    t.test_info = std::format("{} {} {} {}", "heap sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for random numbers of type: ", typeid(T).name());
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged heap sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for random numbers of type:", typeid(T).name());
    run_heap_test<T>(t, avg, baseSize, iterations, fullRandom);

    t.reset();
    t.test_info = std::format("{} {} {} {}", "heap sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for 33% sorted array of random numbers of type:", typeid(T).name());
    avg.reset();
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged heap sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for 33% sorted array of random numbers of type:", typeid(T).name());
    run_heap_test<T>(t, avg, baseSize, iterations, sorted33);

    t.reset();
    t.test_info = std::format("{} {} {} {}", "heap sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for 67% sorted array of random numbers of type:", typeid(T).name());
    avg.reset();
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged heap sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for 67% sorted array of random numbers of type:", typeid(T).name());
    run_heap_test<T>(t, avg, baseSize, iterations, sorted67);

    t.reset();
    t.test_info = std::format("{} {} {} {}", "heap sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for sorted nondesc array of random numbers of type:", typeid(T).name());
    avg.reset();
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged heap sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for sorted nondesc array of random numbers of type:", typeid(T).name());
    run_heap_test<T>(t, avg, baseSize, iterations, sortedAsc);

    t.reset();
    t.test_info = std::format("{} {} {} {}", "heap sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for sorted nonasc array of random numbers of type:", typeid(T).name());
    avg.reset();
    avg.test_info = std::format("{} {} {} {} {}", std::to_string(iterations), "run averaged heap sort test of sizes", std::to_string(baseSize),"*2^k for k in <1,7> for sorted nonasc array of random numbers of type:", typeid(T).name());
    run_heap_test<T>(t, avg, baseSize, iterations, sortedDesc);
}

void showcase_test(const char* filename){
    vector<int> Sedgewick1982 = {65921, 16577, 4193, 1073, 281, 77, 23, 8, 1};
    vector<int> data(filename);
    std::cout<<"Unsorted data: ";
    data.print();
    std::cout<<'\n';
    vector<int> insertData(data);
    vector<int> shellData(data);
    vector<int> heapData(data);
    vector<int> quickDescData(data);
    sorter::insertion_sort(insertData);
    sorter::shell_sort(shellData, Sedgewick1982);
    sorter::quick_sort(data, 0, data.last()-1, [](int left, int right){return right;});
    sorter::heap_sort(heapData);
    sorter::quick_sort_desc(quickDescData, 0, data.last()-1, [](int left, int right){return left;});
    std::cout<<"Insertion sort: ";
    insertData.print();
    std::cout<<'\n';
    std::cout<<"Shell sort: ";
    shellData.print();
    std::cout<<'\n';
    std::cout<<"Heap sort: ";
    heapData.print();
    std::cout<<'\n';
    std::cout<<"Quicksort: ";
    data.print();
    std::cout<<'\n';
    std::cout<<"Quicksort descending: ";
    quickDescData.print();

}