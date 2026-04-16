#include "testing.hpp"
#include <string_view>
#include <stdint.h>
#define PRATT 0
#define CIURA 1
#define KNUTH 2
#define SEDGEWICK 3
#define HIBBARD 4

#define LEFT 1
#define RIGHT 2
#define MIDDLE 0
#define RANDOM 3

/*supported args:
-i -> runs insertion sort
-q -> runs quicksort
    --left -> selects left as pivot
    --right -> selects right as pivot
    --middle -> selects middle as pivot
    --random -> selects random as pivot
-h -> runs heapsort
-s -> runs shellsort
    --pratt -> selects the Pratt gaps
    --ciura -> selects the Ciura gaps
    --knuth -> selects the Knuth gaps
    --sedgewick -> selects the Sedgewick gaps
    --hibbard -> selects the Hibbard gaps
-t filepath -> runs showcase test with data from provided file
*/
int main(const int argc, const char *argv[]){
    constexpr int baseSize = 1000, iterations = 20;

    if (argc < 2) {
        test_insert<float>(baseSize, iterations);
        test_quick<float>(baseSize*100, iterations, LEFT);
        test_heap<float>(baseSize*100, iterations);
        test_shell<float>(baseSize*100, iterations, 3);
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];

        if (arg == "-i") {
            test_insert<int32_t>(baseSize, iterations);
        } else if (arg == "-h") {
            test_heap<int64_t>(baseSize*100, iterations);
        } else if (arg == "-q") {
            int pivot_method = RANDOM;
            if (i + 1 < argc) {
                std::string_view next = argv[i + 1];
                if      (next == "--left")    { pivot_method = LEFT; ++i; }
                else if (next == "--right")   { pivot_method = RIGHT; ++i; }
                else if (next == "--middle")  { pivot_method = MIDDLE; ++i; }
                else if (next == "--random")  { pivot_method = RANDOM; ++i; }
            }
            test_quick<int32_t>(baseSize*100, iterations, pivot_method);
        } else if (arg == "-s") {
            int gap = SEDGEWICK;
            if (i + 1 < argc) {
                std::string_view next = argv[i + 1];
                if      (next == "--pratt")     { gap = PRATT; ++i; }
                else if (next == "--ciura")     { gap = CIURA; ++i; }
                else if (next == "--knuth")     { gap = KNUTH; ++i; }
                else if (next == "--sedgewick") { gap = SEDGEWICK; ++i; }
                else if (next == "--hibbard")   { gap = HIBBARD; ++i; }
            }
            test_shell<int32_t>(baseSize*100, iterations, gap);
        } else if (arg == "-t"){
            if ( i + 1 < argc){
                std::string_view next = argv[i + 1];
                showcase_test(next.data());
            }else{
                std::cerr << "Usage: " << argv[i] << "filepath\n";
                return 1;
            }
        }
    }
    return 0;
}
