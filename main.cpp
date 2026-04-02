#include "heap.hpp"
#include "vector.hpp"
#include "randomizer.hpp"
#include "sorter.hpp"

int main(){
    vector<int> v(15u);
    randomizer randomizer;

    auto intGenerator = [&randomizer](int min, int max){return randomizer.randint(min, max);};
    auto floatGenerator = [&randomizer](float min, float max){return randomizer.randfloat(min, max);};

    v.populate(intGenerator, 0, 10, 0, v.len());
    auto comp_g = [](int a, int b){return a > b;};
    auto comp_s = [](int a, int b){return a < b;};

    v.print();
    //heap<int> h(v, comp_s);
    //h.arr.print();
    //sorter::heap_sort(h, comp_s);
    //sorter::quick_sort(v, 0, v.len()-1, []<typename T>(vector<T>& arr, std::size_t left, std::size_t right){return left;});
    //h.arr.print();
    //sorter::insertion_sort(v);
    sorter::shell_sort(v);
    v.print();


    
    return 0;
}