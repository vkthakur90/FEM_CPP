#pragma once 

#include "program_data.hpp"


template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradA(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd collapse(4) schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            for(size_t mdx = 0; mdx < 3; ++mdx){
                for(size_t ndx = 0; ndx < 3; ++ndx){
                    auto & ref_A = data_ptr->conj_grad.A[idx][jdx][mdx][ndx];
                    auto & ref_mat = data_ptr->discretized.mat[idx][jdx][mdx][ndx];
                    ref_A = ref_mat;
                }
            }
        }
    }
}


template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradBBulk(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd collapse(2) schedule(static)
    for(size_t idx = 1; idx < data_ptr->size - 1; ++idx){
        for(size_t jdx = 1; jdx < data_ptr->size - 1; ++jdx){
            auto & ref_q_rate = data_ptr->bulk_property.q_rate[idx][jdx];
            auto & ref_b = data_ptr->conj_grad.b[idx][jdx];
            
            ref_b = ref_q_rate;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradBBottom(upProgramData<Type, N> & data_ptr) noexcept {    
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & ref_bdry = data_ptr->boundary.bottom[idx];
        auto & ref_b = data_ptr->conj_grad.b[idx][0];
        
        ref_b = ref_bdry;
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradBTop(upProgramData<Type, N> & data_ptr) noexcept {    
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & ref_bdry = data_ptr->boundary.top[idx];
        auto & ref_b = data_ptr->conj_grad.b[idx][data_ptr->size - 1];
        
        ref_b = ref_bdry;
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradBLeft(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & ref_bdry = data_ptr->boundary.left[idx];
        auto & ref_b = data_ptr->conj_grad.b[0][idx];
        
        ref_b = ref_bdry;
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradBRight(upProgramData<Type, N> & data_ptr) noexcept {    
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & ref_bdry = data_ptr->boundary.right[idx];
        auto & ref_b = data_ptr->conj_grad.b[idx][data_ptr->size - 1];
        
        ref_b = ref_bdry;
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradB(upProgramData<Type, N> & data_ptr) noexcept {
    ProgramData_computeConjGradBBulk(data_ptr);
    ProgramData_computeConjGradBTop(data_ptr);
    ProgramData_computeConjGradBBottom(data_ptr);
    ProgramData_computeConjGradBLeft(data_ptr);
    ProgramData_computeConjGradBRight(data_ptr);
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradX(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd collapse(2) schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){ 
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_x = data_ptr->conj_grad.x[idx][jdx];
            ref_x = static_cast<Type>(0);            
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradYBulk(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for collapse(2) schedule(static)
    for(size_t idx = 1; idx < data_ptr->size - 1; ++idx){
        for(size_t jdx = 1; jdx < data_ptr->size - 1; ++jdx){
            auto & ref_y = data_ptr->conj_grad.y[idx][jdx];
            
            Type sum = static_cast<Type>(0);
            for(size_t mdx = 0; mdx < 3; ++mdx){
                for(size_t ndx = 0; ndx < 3; ++ndx){
                    auto & ref_x = data_ptr->conj_grad.x[idx - 1 + mdx][jdx - 1 + ndx];
                    auto & ref_A = data_ptr->conj_grad.A[idx][jdx][mdx][ndx];
                    
                    sum += ref_A * ref_x;
                }
            }
            
            ref_y = sum;
        }
    }       
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradYBottom(upProgramData<Type, N> & data_ptr) noexcept {    
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & ref_bdry = data_ptr->conj_grad.b[idx][0];
        auto & ref_y = data_ptr->conj_grad.y[idx][0];
        
        ref_y = ref_bdry;
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradYTop(upProgramData<Type, N> & data_ptr) noexcept {    
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & ref_bdry = data_ptr->conj_grad.b[idx][data_ptr->size - 1];
        auto & ref_y = data_ptr->conj_grad.y[idx][data_ptr->size - 1];
        
        ref_y = ref_bdry;
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradYLeft(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & ref_bdry = data_ptr->conj_grad.b[0][idx];
        auto & ref_y = data_ptr->conj_grad.y[0][idx];
        
        ref_y = ref_bdry;
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradYRight(upProgramData<Type, N> & data_ptr) noexcept {    
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & ref_bdry = data_ptr->conj_grad.b[idx][data_ptr->size - 1];
        auto & ref_y = data_ptr->conj_grad.y[idx][data_ptr->size - 1];
        
        ref_y = ref_bdry;
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradY(upProgramData<Type, N> & data_ptr) noexcept {
    ProgramData_computeConjGradYBulk(data_ptr);
    ProgramData_computeConjGradYTop(data_ptr);
    ProgramData_computeConjGradYBottom(data_ptr);
    ProgramData_computeConjGradYLeft(data_ptr);
    ProgramData_computeConjGradYRight(data_ptr);
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradR(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd collapse(2) schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_b = data_ptr->conj_grad.b[idx][jdx];
            auto & ref_y = data_ptr->conj_grad.y[idx][jdx];
            auto & ref_r = data_ptr->conj_grad.r[idx][jdx];
            
            ref_r = ref_b - ref_y;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradP(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd collapse(2) schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_p = data_ptr->conj_grad.p[idx][jdx];
            auto & ref_r = data_ptr->conj_grad.r[idx][jdx];
            
            ref_p = ref_r;
        }
    }
}


template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradQBulk(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for collapse(2) schedule(static)
    for(size_t idx = 1; idx < data_ptr->size - 1; ++idx){
        for(size_t jdx = 1; jdx < data_ptr->size - 1; ++jdx){
            auto & ref_q = data_ptr->conj_grad.q[idx][jdx];
            
            Type sum = static_cast<Type>(0);
            for(size_t mdx = 0; mdx < 3; ++mdx){
                for(size_t ndx = 0; ndx < 3; ++ndx){
                    auto & ref_p = data_ptr->conj_grad.p[idx - 1 + mdx][jdx - 1 + ndx];
                    auto & ref_A = data_ptr->conj_grad.A[idx][jdx][mdx][ndx];
                    
                    sum += ref_A * ref_p;
                }
            }
            
            ref_q = sum;
        }
    }       
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradQBottom(upProgramData<Type, N> & data_ptr) noexcept {    
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & ref_bdry = data_ptr->conj_grad.p[idx][0];
        auto & ref_q = data_ptr->conj_grad.q[idx][0];
        
        ref_q = ref_bdry;
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradQTop(upProgramData<Type, N> & data_ptr) noexcept {    
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & ref_bdry = data_ptr->conj_grad.p[idx][data_ptr->size - 1];
        auto & ref_q = data_ptr->conj_grad.q[idx][data_ptr->size - 1];
        
        ref_q = ref_bdry;
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradQLeft(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & ref_bdry = data_ptr->conj_grad.p[0][idx];
        auto & ref_q = data_ptr->conj_grad.q[0][idx];
        
        ref_q = ref_bdry;
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradQRight(upProgramData<Type, N> & data_ptr) noexcept {    
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & ref_bdry = data_ptr->conj_grad.p[idx][data_ptr->size - 1];
        auto & ref_y = data_ptr->conj_grad.q[idx][data_ptr->size - 1];
        
        ref_y = ref_bdry;
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradQ(upProgramData<Type, N> & data_ptr) noexcept {
    ProgramData_computeConjGradQBulk(data_ptr);
    ProgramData_computeConjGradQTop(data_ptr);
    ProgramData_computeConjGradQBottom(data_ptr);
    ProgramData_computeConjGradQLeft(data_ptr);
    ProgramData_computeConjGradQRight(data_ptr);
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradRDotR(upProgramData<Type, N> & data_ptr) noexcept {
    auto & ref_r_dot_r = data_ptr->conj_grad.r_dot_r;
    Type sum = static_cast<Type>(0);
    
    #pragma omp parallel for simd collapse(2) reduction(+:sum) schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_r = data_ptr->conj_grad.r[idx][jdx]; 
            sum += ref_r * ref_r;
        }
    }
    
    ref_r_dot_r = sum;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradPDotQ(upProgramData<Type, N> & data_ptr) noexcept {
    auto & ref_p_dot_q = data_ptr->conj_grad.p_dot_q;
    Type sum = static_cast<Type>(0);
    
    #pragma omp parallel for simd collapse(2) reduction(+:sum) schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_p = data_ptr->conj_grad.p[idx][jdx]; 
            auto & ref_q = data_ptr->conj_grad.q[idx][jdx];
            sum += ref_p * ref_q;
        }
    }
    
    ref_p_dot_q = sum;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradAlpha(upProgramData<Type, N> & data_ptr) noexcept {
    auto & ref_r_dot_r = data_ptr->conj_grad.r_dot_r;
    auto & ref_p_dot_q = data_ptr->conj_grad.p_dot_q;
    auto & ref_alpha = data_ptr->conj_grad.alpha;
    
    ref_alpha = ref_r_dot_r / ref_p_dot_q;
}

template <std::floating_point Type, size_t N>
void ProgramData_updateConjGradX(upProgramData<Type, N> & data_ptr) noexcept {
    auto & ref_alpha = data_ptr->conj_grad.alpha;
    
    #pragma omp parallel for simd collapse(2) schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_x = data_ptr->conj_grad.x[idx][jdx];
            auto & ref_p = data_ptr->conj_grad.p[idx][jdx];
            ref_x += ref_alpha * ref_p;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_updateConjGradR(upProgramData<Type, N> & data_ptr) noexcept {
    auto & ref_alpha = data_ptr->conj_grad.alpha;
    
    #pragma omp parallel for simd collapse(2) schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_r = data_ptr->conj_grad.r[idx][jdx];
            auto & ref_q = data_ptr->conj_grad.q[idx][jdx];
            ref_r -= ref_alpha * ref_q;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradBeta(upProgramData<Type, N> & data_ptr) noexcept {
    auto & ref_beta = data_ptr->conj_grad.beta;
    
    auto prev_r_dot_r = data_ptr->conj_grad.r_dot_r;
    ProgramData_updateConjGradR(data_ptr);
    ProgramData_computeConjGradRDotR(data_ptr);
    auto r_dot_r = data_ptr->conj_grad.r_dot_r;
    
    ref_beta = r_dot_r/prev_r_dot_r;
}

template <std::floating_point Type, size_t N>
void ProgramData_updateConjGradP(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd collapse(2) schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_p = data_ptr->conj_grad.p[idx][jdx];
            auto & ref_r = data_ptr->conj_grad.r[idx][jdx];
            auto & ref_beta = data_ptr->conj_grad.beta;
            
            ref_p *= ref_beta;
            ref_p += ref_r;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_updateConjGradIterStep(upProgramData<Type, N> & data_ptr){
    ProgramData_computeConjGradQ(data_ptr);
    ProgramData_computeConjGradPDotQ(data_ptr);
    ProgramData_computeConjGradAlpha(data_ptr);
    ProgramData_updateConjGradX(data_ptr);
    ProgramData_computeConjGradBeta(data_ptr);
    ProgramData_updateConjGradP(data_ptr);
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGradInit(upProgramData<Type, N> & data_ptr){
    ProgramData_computeConjGradA(data_ptr);
    ProgramData_computeConjGradB(data_ptr);
    ProgramData_computeConjGradX(data_ptr);
    ProgramData_computeConjGradY(data_ptr);
    ProgramData_computeConjGradR(data_ptr);
    ProgramData_computeConjGradP(data_ptr);
    ProgramData_computeConjGradRDotR(data_ptr);
}

template <std::floating_point Type, size_t N>
void ProgramData_computeConjGrad(upProgramData<Type, N> & data_ptr){
    auto & ref_max_iter = data_ptr->conj_grad.max_iter;
    
    ProgramData_computeConjGradInit(data_ptr);
    for(size_t idx = 0; idx < ref_max_iter; ++idx){
        ProgramData_updateConjGradIterStep(data_ptr);
    }
}