#pragma once 

#include <memory>
#include <cstdio>
#include <stdexcept>
#include <cmath>
#include <concepts>
#include <cstddef>

enum ShapeFunction {
    LINEAR,
    CUBIC,
    QUINTIC    
};

template <std::floating_point Type>
inline Type linear_fn(Type x){
    return 1.0f - x; 
}

template <std::floating_point Type>
inline Type cubic_fn(Type x){
    return 1.0f - 3.0f * std::pow(x, 2) + 2.0f * std::pow(x, 3);
}

template <std::floating_point Type>
inline Type quintic_fn(Type x){
    return 1.0f - 10.0 * std::pow(x, 3) + 15.0f * std::pow(x, 4) - 6.0f * std::pow(x, 5);
}

template <std::floating_point Type>
inline Type shape_fn(ShapeFunction shape, Type x){
    Type y;
    
    switch(shape){
    case LINEAR:
        if (x >= 0.0f && x <= 1.0f) {
            y = linear_fn(x);
        } else if (x >= -1.0f && x < 0.0f) {
            y = linear_fn(-x);
        } else {
            y = 0.0f;
        }
        
        break;
        
    case CUBIC:
        if (x >= 0.0f && x <= 1.0f) {
            y = cubic_fn(x);
        } else if (x >= -1.0f && x < 0.0f) {
            y = cubic_fn(-x);
        } else {
            y = 0.0f;
        }
        
        break;
        
    case QUINTIC:
        if (x >= 0.0f && x <= 1.0f) {
            y = quintic_fn(x);
        } else if (x >= -1.0f && x < 0.0f) {
            y = quintic_fn(-x);
        } else {
            y = 0.0f;
        }
        
        break;
        
    default:
        y = 0.0f;
    }
    
    return y;
}

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



