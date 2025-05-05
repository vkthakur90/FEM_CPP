#pragma once

#include "program_data.hpp"
#include "utils.hpp"
#include <memory>

template <std::floating_point Type, size_t N>
void ProgramData_readInputsBulk(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd collapse(2) schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & kxx = data_ptr->bulk_property.k_xx[idx][jdx];
            auto & kxy = data_ptr->bulk_property.k_xy[idx][jdx];
            auto & kyy = data_ptr->bulk_property.k_yy[idx][jdx];
            auto & q_rate = data_ptr->bulk_property.q_rate[idx][jdx];
            
            kxx = 0.01;
            kxy = 0.0;
            kyy = 0.01;
            q_rate = 1.0;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_readInputsBoundary(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & ref_top = data_ptr->boundary.top[idx];
        auto & ref_bottom = data_ptr->boundary.bottom[idx];
        auto & ref_left = data_ptr->boundary.left[idx];
        auto & ref_right = data_ptr->boundary.right[idx];
        
        ref_top = 0.0;
        ref_bottom = 0.0;
        ref_left = 0.0;
        ref_right = 0.0;
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_displayResults(upProgramData<Type, N> & data_ptr){
    auto file = make_unique_file("outputs/fem_soln.txt", "w");
    
    for(size_t idx = 0; idx < data_ptr->size ; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_x = data_ptr->grid.x[idx][jdx];
            auto & ref_y = data_ptr->grid.y[idx][jdx];
            auto & ref_T = data_ptr->conj_grad.x[idx][jdx];
            std::fprintf(
                file.get(),
                "%f\t%f\t\t%f\n",
                ref_x, ref_y, ref_T 
            );
        }
        std::fprintf(file.get(), "\n");
    }       
}

template <std::floating_point Type, size_t N>
void ProgramData_readInputs(upProgramData<Type, N> & data_ptr) {
    ProgramData_readInputsBulk(data_ptr);
    ProgramData_readInputsBoundary(data_ptr);
}