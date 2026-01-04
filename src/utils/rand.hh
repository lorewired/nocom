#pragma once

#include <random>

namespace Game::Utils {

    inline std::mt19937& GetRandomGenerator() {
        static std::random_device rd; 
        static std::mt19937 gen(rd()); 
        return gen;
    }
    
    inline int r32ir(const int l, const int r) {
        std::uniform_int_distribution<int> distribution(l, r);
        return distribution(GetRandomGenerator());
    }
    
    inline long long r64ir(const long long l, const long long r) {
        std::uniform_int_distribution<long long> distribution(l, r);
        return distribution(GetRandomGenerator());
    }

}
 