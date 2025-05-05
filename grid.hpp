#pragma once 

#include "program_data.hpp"
#include <memory>

template <std::floating_point Type, size_t N>
void ProgramData_computeGridDeltaX(upProgramData<Type, N> & data_ptr) noexcept {
    data_ptr->grid.delta_x  = static_cast<float>(data_ptr->sim_box.length_x);
    data_ptr->grid.delta_x /= static_cast<float>(data_ptr->size);
}

template <std::floating_point Type, size_t N>
void ProgramData_computeGridDeltaY(upProgramData<Type, N> & data_ptr) noexcept {
    data_ptr->grid.delta_y  = static_cast<float>(data_ptr->sim_box.length_y);
    data_ptr->grid.delta_y /= static_cast<float>(data_ptr->size);
}

template <std::floating_point Type, size_t N>
void ProgramData_computeGridX(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            data_ptr->grid.x[idx][jdx]  = static_cast<float>(idx);
            data_ptr->grid.x[idx][jdx] *= static_cast<float>(data_ptr->grid.delta_x);
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeGridY(upProgramData<Type, N> & data_ptr) noexcept {    
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            data_ptr->grid.y[idx][jdx]  = static_cast<float>(jdx);
            data_ptr->grid.y[idx][jdx] *= static_cast<float>(data_ptr->grid.delta_y);
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeGrid(upProgramData<Type, N> & data_ptr) noexcept {
    ProgramData_computeGridDeltaX(data_ptr);
    ProgramData_computeGridDeltaY(data_ptr);
    ProgramData_computeGridX(data_ptr);
    ProgramData_computeGridY(data_ptr);
}