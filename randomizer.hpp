#pragma once

#include <random>
#include <concepts>

class randomizer
{
    public:
        randomizer(){
            std::random_device rd;
            this->engine.seed(rd());
        }

    int randint(const int min, const int max){
            if (min > max) throw std::invalid_argument("min must be greater than max");

            std::uniform_int_distribution<int> distribution(min, max);
            return distribution(engine);
        }
        
    char randchar(const char min, const char max){
            if (min > max) throw std::invalid_argument("min must be greater than max");

            std::uniform_int_distribution<char> distribution(min, max);
            return distribution(engine);
        }    

    float randfloat(const float min, const float max){
            if (min > max) throw std::invalid_argument("min must be greater than max");

            std::uniform_real_distribution<float> distribution(min, max);
            return distribution(engine);
        }
        
    double randdouble(const double min, const double max){
            if (min > max) throw std::invalid_argument("min must be greater than max");

            std::uniform_real_distribution<double> distribution(min, max);
            return distribution(engine);
        } 
        
    template <std::floating_point T>    
    T randT(const T min, const T max){
            if (min > max) throw std::invalid_argument("min must be greater than max");

            std::uniform_real_distribution<T> distribution(min, max);
            return distribution(engine);
        }
        
    template <std::integral T>    
    T randT(const T min, const T max){
            if (min > max) throw std::invalid_argument("min must be greater than max");

            std::uniform_int_distribution<T> distribution(min, max);
            return distribution(engine);
        }
    private:
        std::mt19937 engine;

};