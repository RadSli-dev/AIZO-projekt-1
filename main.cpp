#include "heap.hpp"
#include "vector.hpp"
#include "randomizer.hpp"

int main(){
    vector<int> v(10u);
    randomizer randomizer;

    auto intGenerator = [&randomizer](int min, int max){return randomizer.randint(min, max);};
    auto floatGenerator = [&randomizer](float min, float max){return randomizer.randfloat(min, max);};

    v.populate(intGenerator, 0, 10, 0, 10);
    auto comp_g = [](int a, int b){return a > b;};
    heap<int> h(v, comp_g);
    v.print();
    h.arr.print();

    //v.print();
    
    
    return 0;
}