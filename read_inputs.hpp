#pragma once

#include "program_data.hpp"
#include <memory>

template <std::floating_point Type, size_t N>
void ProgramData_readInputsConductivity(std::unique_ptr<ProgramData<Type, N>> & data_ptr) {
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & kxx = data_ptr->bulk_property.k_xx[idx][jdx];
            auto & kxy = data_ptr->bulk_property.k_xy[idx][jdx];
            auto & kyy = data_ptr->bulk_property.k_yy[idx][jdx];
            
            kxx = 0.01f;
            kxy = 0.0f;
            kyy = 0.01f;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_readInputs(std::unique_ptr<ProgramData<Type, N>> & data_ptr) {
    ProgramData_readInputsConductivity(data_ptr);
}