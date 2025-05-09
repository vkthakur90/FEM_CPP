#pragma once 

#include "program_data.hpp"
#include "utils.hpp"
#include <memory>
#include <cmath>


template <std::floating_point Type, size_t N>
void ProgramData_computeQuadU(upProgramData<Type, N> & data_ptr) noexcept {
    constexpr float factor = (static_cast<float>(SIMPSON_SIZE) - 1.0f) / 2.0f;
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        data_ptr->quad.u[idx][1]  = static_cast<float>(idx) - factor;
        data_ptr->quad.u[idx][1] /= factor;
        
        data_ptr->quad.u[idx][0]  = static_cast<float>(idx) - factor - 0.5f;
        data_ptr->quad.u[idx][0] /= factor;

        data_ptr->quad.u[idx][2]  = static_cast<float>(idx) - factor + 0.5f;
        data_ptr->quad.u[idx][2] /= factor;        
    }
}


template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiCurr(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            auto & ref_shape = data_ptr->quad.shape;
            auto & ref_u = data_ptr->quad.u[idx][jdx]; 
            data_ptr->quad.phi.curr[idx][jdx] = shape_fn<Type>(ref_shape, ref_u);
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiNext(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            auto & ref_u = data_ptr->quad.u[idx][jdx];
            auto & ref_shape = data_ptr->quad.shape;
            data_ptr->quad.phi.next[idx][jdx] = shape_fn<Type>(ref_shape, ref_u - 1);
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiPrev(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            auto & ref_u = data_ptr->quad.u[idx][jdx];
            auto & ref_shape = data_ptr->quad.shape;
            data_ptr->quad.phi.prev[idx][jdx] = shape_fn<Type>(ref_shape, ref_u + 1);
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiCurr(upProgramData<Type, N> & data_ptr) noexcept {
    constexpr Type factor = (static_cast<Type>(SIMPSON_SIZE) - 1.0f) / 2.0f;
    constexpr Type h = 1.0f/factor;
    #pragma omp parallel for simd schedule(static) 
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        data_ptr->quad.diff_phi.curr[idx]  = data_ptr->quad.phi.curr[idx][2];
        data_ptr->quad.diff_phi.curr[idx] -= data_ptr->quad.phi.curr[idx][0];
        data_ptr->quad.diff_phi.curr[idx] /= h;
    }
} 

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiPrev(upProgramData<Type, N> & data_ptr) noexcept {
    constexpr Type factor = (static_cast<Type>(SIMPSON_SIZE) - 1.0f) / 2.0f;
    constexpr Type h = 1.0f/factor;
    #pragma omp parallel for simd schedule(static) 
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        data_ptr->quad.diff_phi.prev[idx]  = data_ptr->quad.phi.prev[idx][2];
        data_ptr->quad.diff_phi.prev[idx] -= data_ptr->quad.phi.prev[idx][0];
        data_ptr->quad.diff_phi.prev[idx] /= h;
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiNext(upProgramData<Type, N> & data_ptr) noexcept {
    constexpr Type factor = (static_cast<Type>(SIMPSON_SIZE) - 1.0f) / 2.0f;
    constexpr Type h = 1.0f/factor;
    #pragma omp parallel for simd schedule(static) 
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        data_ptr->quad.diff_phi.next[idx]  = data_ptr->quad.phi.next[idx][2];
        data_ptr->quad.diff_phi.next[idx] -= data_ptr->quad.phi.next[idx][0];
        data_ptr->quad.diff_phi.next[idx] /= h;
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiCurrTimesDiffPhiCurr(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            float temp;
            temp  = data_ptr->quad.diff_phi.curr[idx];
            temp *= data_ptr->quad.diff_phi.curr[idx];
            data_ptr->quad.diff_phi_curr_times_diff_phi.curr[idx][jdx] = temp;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiCurrTimesDiffPhiPrev(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            float temp;
            temp  = data_ptr->quad.diff_phi.curr[idx];
            temp *= data_ptr->quad.diff_phi.prev[idx];
            data_ptr->quad.diff_phi_curr_times_diff_phi.prev[idx][jdx] = temp;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiCurrTimesDiffPhiNext(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            float temp;
            temp  = data_ptr->quad.diff_phi.curr[idx];
            temp *= data_ptr->quad.diff_phi.next[idx];
            data_ptr->quad.diff_phi_curr_times_diff_phi.next[idx][jdx] = temp;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiCurrTimesPhiCurr(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            float temp;
            temp  = data_ptr->quad.diff_phi.curr[idx];
            temp *= data_ptr->quad.phi.curr[idx][jdx];
            data_ptr->quad.diff_phi_curr_times_phi.curr[idx][jdx] = temp;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiCurrTimesPhiPrev(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            float temp;
            temp  = data_ptr->quad.diff_phi.curr[idx];
            temp *= data_ptr->quad.phi.prev[idx][jdx];
            data_ptr->quad.diff_phi_curr_times_phi.prev[idx][jdx] = temp;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiCurrTimesPhiNext(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            float temp;
            temp  = data_ptr->quad.diff_phi.curr[idx];
            temp *= data_ptr->quad.phi.next[idx][jdx];
            data_ptr->quad.diff_phi_curr_times_phi.next[idx][jdx] = temp;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiCurrTimesDiffPhiCurr(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            float temp;
            temp  = data_ptr->quad.phi.curr[idx][jdx];
            temp *= data_ptr->quad.diff_phi.curr[idx];
            data_ptr->quad.phi_curr_times_diff_phi.curr[idx][jdx] = temp;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiCurrTimesDiffPhiPrev(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            float temp;
            temp  = data_ptr->quad.phi.curr[idx][jdx];
            temp *= data_ptr->quad.diff_phi.prev[idx];
            data_ptr->quad.phi_curr_times_diff_phi.prev[idx][jdx] = temp;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiCurrTimesDiffPhiNext(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            float temp;
            temp  = data_ptr->quad.phi.curr[idx][jdx];
            temp *= data_ptr->quad.diff_phi.next[idx];
            data_ptr->quad.phi_curr_times_diff_phi.next[idx][jdx] = temp;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiCurrTimesPhiCurr(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            auto & ref_in = data_ptr->quad.phi.curr[idx][jdx];
            auto & ref_result = data_ptr->quad.phi_curr_times_phi.curr[idx][jdx];
            
            ref_result = ref_in * ref_in;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiCurrTimesPhiPrev(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            auto & ref_curr = data_ptr->quad.phi.curr[idx][jdx];
            auto & ref_other = data_ptr->quad.phi.prev[idx][jdx];
            auto & ref_result = data_ptr->quad.phi_curr_times_phi.prev[idx][jdx];
            
            ref_result = ref_curr * ref_other;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiCurrTimesPhiNext(upProgramData<Type, N> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static) collapse(2)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            auto & ref_curr = data_ptr->quad.phi.curr[idx][jdx];
            auto & ref_other = data_ptr->quad.phi.next[idx][jdx];
            auto & ref_result = data_ptr->quad.phi_curr_times_phi.next[idx][jdx];
            
            ref_result = ref_curr * ref_other;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiCurrTimesDiffPhiCurrInteg(upProgramData<Type, N> & data_ptr) noexcept {
    constexpr Type factor = (static_cast<Type>(SIMPSON_SIZE) - 1.0f) / 2.0f;
    constexpr Type h = 1.0f/factor;
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        data_ptr->quad.simpson[idx]  = data_ptr->quad.diff_phi_curr_times_diff_phi.curr[idx][0];
        data_ptr->quad.simpson[idx] += 4.0f * data_ptr->quad.diff_phi_curr_times_diff_phi.curr[idx][1];
        data_ptr->quad.simpson[idx] += data_ptr->quad.diff_phi_curr_times_diff_phi.curr[idx][2];
        data_ptr->quad.simpson[idx] /= 6.0f;
        data_ptr->quad.simpson[idx] *= h;
    }
    
    Type sum = 0;
    #pragma omp parallel for simd schedule(static) reduction(+:sum)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        sum += data_ptr->quad.simpson[idx];
    }
    
    data_ptr->quad.diff_phi_curr_times_diff_phi.curr_integ = sum;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiCurrTimesDiffPhiPrevInteg(upProgramData<Type, N> & data_ptr) noexcept {
    constexpr Type factor = (static_cast<Type>(SIMPSON_SIZE) - 1.0f) / 2.0f;
    constexpr Type h = 1.0f/factor;
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        data_ptr->quad.simpson[idx]  = data_ptr->quad.diff_phi_curr_times_diff_phi.prev[idx][0];
        data_ptr->quad.simpson[idx] += 4.0f * data_ptr->quad.diff_phi_curr_times_diff_phi.prev[idx][1];
        data_ptr->quad.simpson[idx] += data_ptr->quad.diff_phi_curr_times_diff_phi.prev[idx][2];
        data_ptr->quad.simpson[idx] /= 6.0f;
        data_ptr->quad.simpson[idx] *= h;
    }
    
    Type sum = 0;
    #pragma omp parallel for simd schedule(static) reduction(+:sum)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        sum += data_ptr->quad.simpson[idx];
    }
    
    data_ptr->quad.diff_phi_curr_times_diff_phi.prev_integ = sum;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiCurrTimesDiffPhiNextInteg(upProgramData<Type, N> & data_ptr) noexcept {
    constexpr Type factor = (static_cast<Type>(SIMPSON_SIZE) - 1.0f) / 2.0f;
    constexpr Type h = 1.0f/factor;
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        data_ptr->quad.simpson[idx]  = data_ptr->quad.diff_phi_curr_times_diff_phi.next[idx][0];
        data_ptr->quad.simpson[idx] += 4.0f * data_ptr->quad.diff_phi_curr_times_diff_phi.next[idx][1];
        data_ptr->quad.simpson[idx] += data_ptr->quad.diff_phi_curr_times_diff_phi.next[idx][2];
        data_ptr->quad.simpson[idx] /= 6.0f;
        data_ptr->quad.simpson[idx] *= h;
    }
    
    Type sum = 0;
    #pragma omp parallel for simd schedule(static) reduction(+:sum)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        sum += data_ptr->quad.simpson[idx];
    }
    
    data_ptr->quad.diff_phi_curr_times_diff_phi.next_integ = sum;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiCurrTimesPhiCurrInteg(upProgramData<Type, N> & data_ptr) noexcept {
    constexpr Type factor = (static_cast<Type>(SIMPSON_SIZE) - 1.0f) / 2.0f;
    constexpr Type h = 1.0f/factor;
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        data_ptr->quad.simpson[idx]  = data_ptr->quad.diff_phi_curr_times_phi.curr[idx][0];
        data_ptr->quad.simpson[idx] += 4.0f * data_ptr->quad.diff_phi_curr_times_phi.curr[idx][1];
        data_ptr->quad.simpson[idx] += data_ptr->quad.diff_phi_curr_times_phi.curr[idx][2];
        data_ptr->quad.simpson[idx] /= 6.0f;
        data_ptr->quad.simpson[idx] *= h;
    }
    
    Type sum = 0;
    #pragma omp parallel for simd schedule(static) reduction(+:sum)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        sum += data_ptr->quad.simpson[idx];
    }
    
    data_ptr->quad.diff_phi_curr_times_phi.curr_integ = sum;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiCurrTimesPhiPrevInteg(upProgramData<Type, N> & data_ptr) noexcept {
    constexpr Type factor = (static_cast<Type>(SIMPSON_SIZE) - 1.0f) / 2.0f;
    constexpr Type h = 1.0f/factor;
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        data_ptr->quad.simpson[idx]  = data_ptr->quad.diff_phi_curr_times_phi.prev[idx][0];
        data_ptr->quad.simpson[idx] += 4.0f * data_ptr->quad.diff_phi_curr_times_phi.prev[idx][1];
        data_ptr->quad.simpson[idx] += data_ptr->quad.diff_phi_curr_times_phi.prev[idx][2];
        data_ptr->quad.simpson[idx] /= 6.0f;
        data_ptr->quad.simpson[idx] *= h;
    }
    
    Type sum = 0;
    #pragma omp parallel for simd schedule(static) reduction(+:sum)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        sum += data_ptr->quad.simpson[idx];
    }
    
    data_ptr->quad.diff_phi_curr_times_phi.prev_integ = sum;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiCurrTimesPhiNextInteg(upProgramData<Type, N> & data_ptr) noexcept {
    constexpr Type factor = (static_cast<Type>(SIMPSON_SIZE) - 1.0f) / 2.0f;
    constexpr Type h = 1.0f/factor;
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        data_ptr->quad.simpson[idx]  = data_ptr->quad.diff_phi_curr_times_phi.next[idx][0];
        data_ptr->quad.simpson[idx] += 4.0f * data_ptr->quad.diff_phi_curr_times_phi.next[idx][1];
        data_ptr->quad.simpson[idx] += data_ptr->quad.diff_phi_curr_times_phi.next[idx][2];
        data_ptr->quad.simpson[idx] /= 6.0f;
        data_ptr->quad.simpson[idx] *= h;
    }
    
    Type sum = 0;
    #pragma omp parallel for simd schedule(static) reduction(+:sum)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        sum += data_ptr->quad.simpson[idx];
    }
    
    data_ptr->quad.diff_phi_curr_times_phi.next_integ = sum;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiCurrTimesDiffPhiCurrInteg(upProgramData<Type, N> & data_ptr) noexcept {
    constexpr Type factor = (static_cast<Type>(SIMPSON_SIZE) - 1.0f) / 2.0f;
    constexpr Type h = 1.0f/factor;
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        data_ptr->quad.simpson[idx]  = data_ptr->quad.phi_curr_times_diff_phi.curr[idx][0];
        data_ptr->quad.simpson[idx] += 4.0f * data_ptr->quad.phi_curr_times_diff_phi.curr[idx][1];
        data_ptr->quad.simpson[idx] += data_ptr->quad.phi_curr_times_diff_phi.curr[idx][2];
        data_ptr->quad.simpson[idx] /= 6.0f;
        data_ptr->quad.simpson[idx] *= h;
    }
    
    Type sum = 0;
    #pragma omp parallel for simd schedule(static) reduction(+:sum)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        sum += data_ptr->quad.simpson[idx];
    }
    
    data_ptr->quad.phi_curr_times_diff_phi.curr_integ = sum;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiCurrTimesDiffPhiPrevInteg(upProgramData<Type, N> & data_ptr) noexcept {
    constexpr Type factor = (static_cast<Type>(SIMPSON_SIZE) - 1.0f) / 2.0f;
    constexpr Type h = 1.0f/factor;
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        data_ptr->quad.simpson[idx]  = data_ptr->quad.phi_curr_times_diff_phi.prev[idx][0];
        data_ptr->quad.simpson[idx] += 4.0f * data_ptr->quad.phi_curr_times_diff_phi.prev[idx][1];
        data_ptr->quad.simpson[idx] += data_ptr->quad.phi_curr_times_diff_phi.prev[idx][2];
        data_ptr->quad.simpson[idx] /= 6.0f;
        data_ptr->quad.simpson[idx] *= h;
    }
    
    float sum = 0;
    #pragma omp parallel for simd schedule(static) reduction(+:sum)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        sum += data_ptr->quad.simpson[idx];
    }
    
    data_ptr->quad.phi_curr_times_diff_phi.prev_integ = sum;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiCurrTimesDiffPhiNextInteg(upProgramData<Type, N> & data_ptr) noexcept {
    constexpr Type factor = (static_cast<Type>(SIMPSON_SIZE) - 1.0f) / 2.0f;
    constexpr Type h = 1.0f/factor;
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        data_ptr->quad.simpson[idx]  = data_ptr->quad.phi_curr_times_diff_phi.next[idx][0];
        data_ptr->quad.simpson[idx] += 4.0f * data_ptr->quad.phi_curr_times_diff_phi.next[idx][1];
        data_ptr->quad.simpson[idx] += data_ptr->quad.phi_curr_times_diff_phi.next[idx][2];
        data_ptr->quad.simpson[idx] /= 6.0f;
        data_ptr->quad.simpson[idx] *= h;
    }
    
    Type sum = 0;
    #pragma omp parallel for simd schedule(static) reduction(+:sum)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        sum += data_ptr->quad.simpson[idx];
    }
    
    data_ptr->quad.phi_curr_times_diff_phi.next_integ = sum;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiCurrTimesPhiCurrInteg(upProgramData<Type, N> & data_ptr) noexcept {
    constexpr Type factor = (static_cast<Type>(SIMPSON_SIZE) - 1.0f) / 2.0f;
    constexpr Type h = 1.0f/factor;
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        data_ptr->quad.simpson[idx]  = data_ptr->quad.phi_curr_times_phi.curr[idx][0];
        data_ptr->quad.simpson[idx] += 4.0f * data_ptr->quad.phi_curr_times_phi.curr[idx][1];
        data_ptr->quad.simpson[idx] += data_ptr->quad.phi_curr_times_phi.curr[idx][2];
        data_ptr->quad.simpson[idx] /= 6.0f;
        data_ptr->quad.simpson[idx] *= h;
    }
    
    Type sum = 0;
    #pragma omp parallel for simd schedule(static) reduction(+:sum)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        sum += data_ptr->quad.simpson[idx];
    }
    
    data_ptr->quad.phi_curr_times_phi.curr_integ = sum;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiCurrTimesPhiPrevInteg(upProgramData<Type, N> & data_ptr) noexcept {
    constexpr Type factor = (static_cast<Type>(SIMPSON_SIZE) - 1.0f) / 2.0f;
    constexpr Type h = 1.0f/factor;
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        data_ptr->quad.simpson[idx]  = data_ptr->quad.phi_curr_times_phi.prev[idx][0];
        data_ptr->quad.simpson[idx] += 4.0f * data_ptr->quad.phi_curr_times_phi.prev[idx][1];
        data_ptr->quad.simpson[idx] += data_ptr->quad.phi_curr_times_phi.prev[idx][2];
        data_ptr->quad.simpson[idx] /= 6.0f;
        data_ptr->quad.simpson[idx] *= h;
    }
    
    Type sum = 0;
    #pragma omp parallel for simd schedule(static) reduction(+:sum)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        sum += data_ptr->quad.simpson[idx];
    }
    
    data_ptr->quad.phi_curr_times_phi.prev_integ = sum;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiCurrTimesPhiNextInteg(upProgramData<Type, N> & data_ptr) noexcept {
    constexpr Type factor = (static_cast<Type>(SIMPSON_SIZE) - 1.0f) / 2.0f;
    constexpr Type h = 1.0f/factor;
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        data_ptr->quad.simpson[idx]  = data_ptr->quad.phi_curr_times_phi.next[idx][0];
        data_ptr->quad.simpson[idx] += 4.0f * data_ptr->quad.phi_curr_times_phi.next[idx][1];
        data_ptr->quad.simpson[idx] += data_ptr->quad.phi_curr_times_phi.next[idx][2];
        data_ptr->quad.simpson[idx] /= 6.0f;
        data_ptr->quad.simpson[idx] *= h;
    }
    
    Type sum = 0;
    #pragma omp parallel for simd schedule(static) reduction(+:sum)
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        sum += data_ptr->quad.simpson[idx];
    }
    
    data_ptr->quad.phi_curr_times_phi.next_integ = sum;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhi(upProgramData<Type, N> & data_ptr) noexcept {
    ProgramData_computeQuadU(data_ptr);
    ProgramData_computeQuadPhiCurr(data_ptr);
    ProgramData_computeQuadPhiPrev(data_ptr);
    ProgramData_computeQuadPhiNext(data_ptr);
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhi(upProgramData<Type, N> & data_ptr) noexcept {
    ProgramData_computeQuadDiffPhiCurr(data_ptr);
    ProgramData_computeQuadDiffPhiPrev(data_ptr);
    ProgramData_computeQuadDiffPhiNext(data_ptr);
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiCurrTimesDiffPhi(upProgramData<Type, N> & data_ptr) noexcept {
    ProgramData_computeQuadDiffPhiCurrTimesDiffPhiCurr(data_ptr);
    ProgramData_computeQuadDiffPhiCurrTimesDiffPhiPrev(data_ptr);
    ProgramData_computeQuadDiffPhiCurrTimesDiffPhiNext(data_ptr);
    ProgramData_computeQuadDiffPhiCurrTimesDiffPhiCurrInteg(data_ptr);
    ProgramData_computeQuadDiffPhiCurrTimesDiffPhiPrevInteg(data_ptr);
    ProgramData_computeQuadDiffPhiCurrTimesDiffPhiNextInteg(data_ptr);
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadDiffPhiCurrTimesPhi(upProgramData<Type, N> & data_ptr) noexcept {
    ProgramData_computeQuadDiffPhiCurrTimesPhiCurr(data_ptr);
    ProgramData_computeQuadDiffPhiCurrTimesPhiPrev(data_ptr);
    ProgramData_computeQuadDiffPhiCurrTimesPhiNext(data_ptr);
    ProgramData_computeQuadDiffPhiCurrTimesPhiCurrInteg(data_ptr);
    ProgramData_computeQuadDiffPhiCurrTimesPhiPrevInteg(data_ptr);
    ProgramData_computeQuadDiffPhiCurrTimesPhiNextInteg(data_ptr);
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiCurrTimesDiffPhi(upProgramData<Type, N> & data_ptr) noexcept {
    ProgramData_computeQuadPhiCurrTimesDiffPhiCurr(data_ptr);
    ProgramData_computeQuadPhiCurrTimesDiffPhiPrev(data_ptr);
    ProgramData_computeQuadPhiCurrTimesDiffPhiNext(data_ptr);
    ProgramData_computeQuadPhiCurrTimesDiffPhiCurrInteg(data_ptr);
    ProgramData_computeQuadPhiCurrTimesDiffPhiPrevInteg(data_ptr);
    ProgramData_computeQuadPhiCurrTimesDiffPhiNextInteg(data_ptr);
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuadPhiCurrTimesPhi(upProgramData<Type, N> & data_ptr) noexcept {
    ProgramData_computeQuadPhiCurrTimesPhiCurr(data_ptr);
    ProgramData_computeQuadPhiCurrTimesPhiPrev(data_ptr);
    ProgramData_computeQuadPhiCurrTimesPhiNext(data_ptr);
    ProgramData_computeQuadPhiCurrTimesPhiCurrInteg(data_ptr);
    ProgramData_computeQuadPhiCurrTimesPhiPrevInteg(data_ptr);
    ProgramData_computeQuadPhiCurrTimesPhiNextInteg(data_ptr);
}

template <std::floating_point Type, size_t N>
void ProgramData_computeQuad(upProgramData<Type, N> & data_ptr) noexcept {
    ProgramData_computeQuadPhi(data_ptr);
    ProgramData_computeQuadDiffPhi(data_ptr);
    ProgramData_computeQuadDiffPhiCurrTimesDiffPhi(data_ptr);
    ProgramData_computeQuadDiffPhiCurrTimesPhi(data_ptr);
    ProgramData_computeQuadPhiCurrTimesDiffPhi(data_ptr);
    ProgramData_computeQuadPhiCurrTimesPhi(data_ptr);
}
