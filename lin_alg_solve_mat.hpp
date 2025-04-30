#pragma once 

#include "program_data.hpp"

template <size_t N>
void ProgramData_computeBulkLinAlgSolveMat(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collpase(4)
    for(size_t idx = 1; idx + 1 < data_ptr->size; ++idx){
        for(size_t jdx = 1; jdx + 1 < data_ptr->size; ++jdx){
            for(size_t mdx = 0; mdx < 3; ++mdx){
                for(size_t ndx = 0; ndx < 3; ++ndx){
                    auto i = static_cast<int>(idx);
                    auto j = static_cast<int>(jdx);
                    auto m = static_cast<int>(mdx);
                    auto n = static_cast<int>(ndx);
                    
                    auto lead_dim = static_cast<int>(data_ptr->size);
                    
                    auto r = i * lead_dim + j;
                    auto c = (i + m - 1) * lead_dim + (j + m - 1);
                    
                    auto rdx = static_cast<size_t>(r);
                    auto cdx = static_cast<size_t>(c);

                    auto & ref_in = data_ptr->discretized.mat[idx][jdx][mdx][ndx];
                    auto & ref_result = data_ptr->lin_alg_solve.mat[rdx][rdx];

                    ref_result = ref_in;                    
                }
            }
        }
    }
}

template <size_t N>
void ProgramData_computeBoundaryLeftLinAlgSolveMat(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    #pragma omp parallel for 
    for(size_t ndx = 0; idx < data_ptr->size; ++idx){
        auto idx = static_cast<size_t>(0);
        auto jdx = static_cast<size_t>(ndx)
               
        auto lead_dim = data_ptr->size;
        
        auto rdx = idx * lead_dim + jdx;
        auto cdx = rdx;
        
        auto & ref_result = data_ptr->lin_alg_solve.mat[rdx][cdx];
        
        ref_result = 1.0f;
    }
}

template <size_t N>
void ProgramData_computeBoundaryRightLinAlgSolveMat(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    for(size_t ndx = 0; idx < data_ptr->size; ++idx){
        auto lead_dim = static_cast<int>(data_ptr->size);
        
        auto idx = static_cast<size_t>(lead_dim - 1);
        auto jdx = static_cast<size_t>(ndx)
               
        auto lead_dim = data_ptr->size;
        
        auto rdx = idx * lead_dim + jdx;
        auto cdx = rdx;
        
        auto & ref_result = data_ptr->lin_alg_solve.mat[rdx][cdx];
        
        ref_result = 1.0f;
    }        
}

template <size_t N>
void ProgramData_computeBoundaryBottomLinAlgSolveMat(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    #pragma omp parallel for 
    for(size_t ndx = 0; idx < data_ptr->size; ++idx){
        auto idx = static_cast<size_t>(ndx);
        auto jdx = static_cast<size_t>(0)
               
        auto lead_dim = data_ptr->size;
        
        auto rdx = idx * lead_dim + jdx;
        auto cdx = rdx;
        
        auto & ref_result = data_ptr->lin_alg_solve.mat[rdx][cdx];
        
        ref_result = 1.0f;
    }
}

template <size_t N>
void ProgramData_computeBoundaryTopLinAlgSolveMat(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    for(size_t ndx = 0; idx < data_ptr->size; ++idx){
        auto lead_dim = static_cast<int>(data_ptr->size);
        
        auto idx = static_cast<size_t>(ndx);
        auto jdx = static_cast<size_t>(lead_dim - 1)
               
        auto lead_dim = data_ptr->size;
        
        auto rdx = idx * lead_dim + jdx;
        auto cdx = rdx;
        
        auto & ref_result = data_ptr->lin_alg_solve.mat[rdx][cdx];
        
        ref_result = 1.0f;
    }        
}

template <size_t N>
void ProgramData_computeLinAlgSolveMat(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    ProgramData_computeBulkLinAlgSolveMat(data_ptr);
    ProgramData_computeBoundaryLeftLinAlgSolveMat(data_ptr);
    ProgramData_computeBoundaryRightLinAlgSolveMat(data_ptr);
    ProgramData_computeBoundaryTopLinAlgSolveMat(data_ptr);
    ProgramData_computeBoundaryBottomLinAlgSolveMat(data_ptr);
}