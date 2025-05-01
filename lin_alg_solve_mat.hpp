#pragma once 

#include "program_data.hpp"

template <size_t N>
void ProgramData_computeBulkLinAlgSolveMatIdentity(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    auto & NUM = data_ptr->size;
    
    #pragma omp parallel for simd collapse(2) schedule(static)
    for(size_t idx = 0; idx < NUM * NUM; ++idx){
        for(size_t jdx = 0; jdx < NUM * NUM; ++jdx){
            auto & ref_result = data_ptr->lin_alg_solve.mat[idx][jdx];
            ref_result = (idx == jdx) ? 1.0f : 0.0f;
        }
    }    
}

template <size_t N>
void ProgramData_computeBulkLinAlgSolveMat(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    #pragma omp parallel for simd collapse(4) schedule(static)
    for(size_t idx = 1; idx < data_ptr->size - 1; ++idx){
        for(size_t jdx = 1; jdx < data_ptr->size - 1; ++jdx){
            for(size_t mdx = 0; mdx < 3; ++mdx){
                for(size_t ndx = 0; ndx < 3; ++ndx){                    
                    size_t NUM = data_ptr->size;
                    
                    size_t rdx = idx * NUM + jdx;
                    size_t cdx = (idx + mdx - 1) * NUM + (jdx + ndx - 1);

                    auto & ref_in = data_ptr->discretized.mat[idx][jdx][mdx][ndx];
                    auto & ref_result = data_ptr->lin_alg_solve.mat[rdx][cdx];

                    ref_result = ref_in;                    
                }
            }
        }
    }
}



template <size_t N>
void ProgramData_computeLinAlgSolveMat(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    ProgramData_computeBulkLinAlgSolveMatIdentity(data_ptr);
    ProgramData_computeBulkLinAlgSolveMat(data_ptr);
}