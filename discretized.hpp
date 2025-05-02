#pragma once 

#include "program_data.hpp"

template <std::floating_point Type, size_t N>
void ProgramData_computeDescretizedMatXX(std::unique_ptr<ProgramData<Type, N>> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(4)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            for(size_t mdx = 0; mdx < 3; ++mdx){
                for(size_t ndx = 0; ndx < 3; ++ndx){
                    auto & ref_k = data_ptr->bulk_property.k_xx[idx][jdx];
                    auto & ref_delta_x = data_ptr->grid.delta_x;
                    auto & ref_coeff = data_ptr->integrals.coeff_xx[mdx][ndx];
                    auto & ref_result = data_ptr->discretized.mat_xx[idx][jdx][mdx][ndx];
                    
                    ref_result = ref_coeff * ref_k / (ref_delta_x * ref_delta_x);
                }    
            }
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeDescretizedMatXY(std::unique_ptr<ProgramData<Type, N>> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(4)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            for(size_t mdx = 0; mdx < 3; ++mdx){
                for(size_t ndx = 0; ndx < 3; ++ndx){
                    auto & ref_k = data_ptr->bulk_property.k_xy[idx][jdx];
                    auto & ref_delta_x = data_ptr->grid.delta_x;
                    auto & ref_delta_y = data_ptr->grid.delta_y;
                    auto & ref_coeff = data_ptr->integrals.coeff_xy[mdx][ndx];
                    auto & ref_result = data_ptr->discretized.mat_xy[idx][jdx][mdx][ndx];
                    
                    ref_result = ref_coeff * ref_k / (ref_delta_x * ref_delta_y);
                }    
            }
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeDescretizedMatYY(std::unique_ptr<ProgramData<Type, N>> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(4)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            for(size_t mdx = 0; mdx < 3; ++mdx){
                for(size_t ndx = 0; ndx < 3; ++ndx){
                    auto & ref_k = data_ptr->bulk_property.k_yy[idx][jdx];
                    auto & ref_delta_y = data_ptr->grid.delta_y;
                    auto & ref_coeff = data_ptr->integrals.coeff_yy[mdx][ndx];
                    auto & ref_result = data_ptr->discretized.mat_yy[idx][jdx][mdx][ndx];
                    
                    ref_result = ref_coeff * ref_k / (ref_delta_y * ref_delta_y);
                }    
            }
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeDescretizedMat(std::unique_ptr<ProgramData<Type, N>> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(4)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            for(size_t mdx = 0; mdx < 3; ++mdx){
                for(size_t ndx = 0; ndx < 3; ++ndx){
                    auto & ref_mat_xx = data_ptr->discretized.mat_xx[idx][jdx][mdx][ndx];
                    auto & ref_mat_xy = data_ptr->discretized.mat_xy[idx][jdx][mdx][ndx];
                    auto & ref_mat_yy = data_ptr->discretized.mat_yy[idx][jdx][mdx][ndx];
                    auto & ref_mat = data_ptr->discretized.mat[idx][jdx][mdx][ndx];
                    
                    ref_mat  = ref_mat_xx;
                    ref_mat += ref_mat_xy;
                    ref_mat += ref_mat_yy;
                }    
            }
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeDescretizedGenRate(std::unique_ptr<ProgramData<Type, N>> & data_ptr) noexcept {
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_in = data_ptr->bulk_property.q_rate[idx][jdx];
            auto & ref_result = data_ptr->discretized.gen_rate[idx][jdx];

            ref_result = ref_in;            
        }
    } 
}

template <std::floating_point Type, size_t N>
void ProgramData_computeDescretized(std::unique_ptr<ProgramData<Type, N>> & data_ptr) noexcept {
    ProgramData_computeDescretizedMatXX(data_ptr);
    ProgramData_computeDescretizedMatXY(data_ptr);
    ProgramData_computeDescretizedMatYY(data_ptr);
    ProgramData_computeDescretizedMat(data_ptr);
    ProgramData_computeDescretizedGenRate(data_ptr);
}