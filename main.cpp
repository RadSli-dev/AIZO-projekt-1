#include "testing.hpp"

/*typedef struct{
    std::chrono::duration<double> __insertion;
    std::chrono::duration<double> __shell;
    std::chrono::duration<double> __heap;
    std::chrono::duration<double> __quick;
    std::size_t test_size;
}test_result;

test_result test_int_random(std::size_t test_size){
    randomizer randomizer;
    test_result t;
    t.test_size = test_size;
    
    auto intGenerator = [&randomizer](int min, int max){return randomizer.randint(min, max);};
    auto comp_s = [](int a, int b){return a < b;};
    auto pivot_s = []<typename T>(vector<T>& arr, std::size_t left, std::size_t right){return right;};
    
    
    vector<int> data1(t.test_size);
    data1.populate(intGenerator, INT_MIN, INT_MAX, 0, t.test_size);
    vector<int> data2;
    vector<int> data3;
    data1.copy_to(data2);
    data1.copy_to(data3);
    heap<int> data4(data1, comp_s);
    
    const auto start_insertion{std::chrono::steady_clock::now()};
    sorter::insertion_sort(data1);
    const auto finish_insertion{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_insertion{finish_insertion - start_insertion};
    t.__insertion = elapsed_insertion;
    
    const auto start_shell{std::chrono::steady_clock::now()};
    sorter::shell_sort(data2);
    const auto finish_shell{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_shell{finish_shell - start_shell};
    t.__shell = elapsed_shell;
    
    const auto start_quick{std::chrono::steady_clock::now()};
    sorter::quick_sort(data3, 0, data3.len() - 1, pivot_s);
    const auto finish_quick{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_quick{finish_quick - start_quick};
    t.__quick = elapsed_quick;
    
    const auto start_heap{std::chrono::steady_clock::now()};
    sorter::heap_sort(data4, comp_s);
    const auto finisht_heap{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_heap{finisht_heap - start_heap};
    t.__heap = elapsed_heap;
    
    return t;
}

void run_tests(std::size_t test_size){
    std::cout<<"==================\n";
    std::cout<<test_size<<'\n';
    
    test_result test10k = test_int_random(test_size);
    std::cout<<test10k.__insertion<<'\n';
    std::cout<<test10k.__shell<<'\n';
    std::cout<<test10k.__quick<<'\n';
    std::cout<<test10k.__heap<<'\n';
    
    std::chrono::duration<double> total_insertion;
    std::chrono::duration<double> total_shell;
    std::chrono::duration<double> total_quick;
    std::chrono::duration<double> total_heap;
    
    for(int i = 0; i<20; i++){
        test10k = test_int_random(test_size);
        total_insertion += test10k.__insertion;
        total_shell += test10k.__shell;
        total_quick += test10k.__quick;
        total_heap += test10k.__heap;
    }
    
    total_insertion /= test_size;
    total_shell /= test_size;
    total_quick /= test_size;
    total_heap /= test_size;
    std::cout<<"==================\n";
    std::cout<<test10k.__insertion<<'\n';
    std::cout<<test10k.__shell<<'\n';
    std::cout<<test10k.__quick<<'\n';
    std::cout<<test10k.__heap<<'\n';
    std::cout<<"==================\n";
}*/


int main(){
    test_insert('a');
    
    return 0;
}