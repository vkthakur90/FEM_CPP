#pragma once 

#include "program_data.hpp"
#include <memory>
#include <cmath>

template <size_t N>
void ProgramData_computeQuadU(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < 2001; ++idx){
        data_ptr->quad.u[idx][1]  = static_cast<float>(idx - 1000);
        data_ptr->quad.u[idx][1] /= static_cast<float>(1000);
        
        data_ptr->quad.u[idx][0]  = static_cast<float>(idx - 1000) - 0.5f;
        data_ptr->quad.u[idx][0] /= static_cast<float>(1000);

        data_ptr->quad.u[idx][2]  = static_cast<float>(idx - 1000) + 0.5f;
        data_ptr->quad.u[idx][2] /= static_cast<float>(1000);        
    }
}


template <size_t N>
void ProgramData_computePhiCurr(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < 2001; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            data_ptr->quad.phi.curr[idx][jdx] = 1 - std::fabs(data_ptr->quad.phi.u[idx][jdx]);
        }
    }
}