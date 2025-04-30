#pragma once 

#include <memory>
#include <cstdio>
#include <stdexcept>
#include <cmath>

float linear_shape_fn(float x){
    float y;
    
    if (x >= 0.0f && x <= 1.0f) {
        y = 1.0f - x;
    } else if (x >= -1.0f && x < 0.0f) {
        y = 1.0f + x;
    } else {
        y = 0.0f;
    }
    
    return y;
}

float cubic_shape_fn(float x){
    float y;
    
    if (x >= 0.0f && x <= 1.0f) {
        y = 1.0f - 3.0f * std::pow(x, 2) + 2.0f * std::pow(x, 3);
    } else if (x >= -1.0f && x < 0.0f) {
        y = 1.0f - 3.0f * std::pow(-x, 2) + 2.0f * std::pow(-x, 3);
    } else {
        y = 0.0f;
    }
    
    return y;
}

// Factory: opens a FILE* and wraps it in unique_ptr with a lambda deleter.
// Throws std::runtime_error if fopen fails.
auto make_unique_file(const char* filename, const char* mode) {
    auto closer = [](FILE* f) noexcept {
        if (f) std::fclose(f);
    };

    FILE* raw = std::fopen(filename, mode);  
    if (!raw) {
        // fopen returns nullptr on failure
        throw std::runtime_error(std::string("Unable to open file '")
                                 + filename + "'");  // report which file failed
    }

    return std::unique_ptr<FILE, decltype(closer)>(raw, closer);
}



