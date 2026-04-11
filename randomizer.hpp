#pragma once

#include <random>

class randomizer
{
    public:
        randomizer(){
            std::random_device rd;
            this->engine.seed(rd());
        }

    int randint(int min, int max){
            if (min > max) throw std::invalid_argument("min must be greater than max");

            std::uniform_int_distribution<int> distribution(min, max);
            return distribution(engine);
        }
        
    char randchar(char min, char max){
            if (min > max) throw std::invalid_argument("min must be greater than max");

            std::uniform_int_distribution<char> distribution(min, max);
            return distribution(engine);
        }    

    float randfloat(float min, float max){
            if (min > max) throw std::invalid_argument("min must be greater than max");

            std::uniform_real_distribution<float> distribution(min, max);
            return distribution(engine);
        }
        
    double randdouble(double min, double max){
            if (min > max) throw std::invalid_argument("min must be greater than max");

            std::uniform_real_distribution<double> distribution(min, max);
            return distribution(engine);
        } 
        
    template <typename T>    
    T randT(T min, T max){
            if (min > max) throw std::invalid_argument("min must be greater than max");

            std::uniform_real_distribution<T> distribution(min, max);
            return distribution(engine);
        }
    private:
        std::mt19937 engine;

};