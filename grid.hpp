#pragma once 

#include "program_data.hpp"
#include <memory>

template <size_t N>
void ProgramData_computeGridDeltaX(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    data_ptr->grid.delta_x  = static_cast<float>(data_ptr->sim_box.length_x);
    data_ptr->grid.delta_x /= static_cast<float>(data_ptr->size);
}

template <size_t N>
void ProgramData_computeGridDeltaY(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    data_ptr->grid.delta_y  = static_cast<float>(data_ptr->sim_box.length_y);
    data_ptr->grid.delta_y /= static_cast<float>(data_ptr->size);
}

template <size_t N>
void ProgramData_computeGridX(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            data_ptr->grid.x[idx][jdx]  = static_cast<float>(idx);
            data_ptr->grid.x[idx][jdx] *= static_cast<float>(data_ptr->grid.delta_x);
        }
    }
}

template <size_t N>
void ProgramData_computeGridY(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {    
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            data_ptr->grid.y[idx][jdx]  = static_cast<float>(jdx);
            data_ptr->grid.y[idx][jdx] *= static_cast<float>(data_ptr->grid.delta_y);
        }
    }
}

template <size_t N>
void ProgramData_computeGrid(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    ProgramData_computeGridDeltaX(data_ptr);
    ProgramData_computeGridDeltaY(data_ptr);
    ProgramData_computeGridX(data_ptr);
    ProgramData_computeGridY(data_ptr);
}