#pragma once

#include "program_data.hpp"

template <std::floating_point Type, size_t N>
void ProgramData_computeIntegralsDiffPhiCurrTimesDiffPhi(upProgramData<Type, N> & data_ptr) noexcept {
    data_ptr->integrals.diff_phi_curr_times_diff_phi[0] = data_ptr->quad.diff_phi_curr_times_diff_phi.prev_integ;
    data_ptr->integrals.diff_phi_curr_times_diff_phi[1] = data_ptr->quad.diff_phi_curr_times_diff_phi.curr_integ;
    data_ptr->integrals.diff_phi_curr_times_diff_phi[2] = data_ptr->quad.diff_phi_curr_times_diff_phi.next_integ;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeIntegralsDiffPhiCurrTimesPhi(upProgramData<Type, N> & data_ptr) noexcept {
    data_ptr->integrals.diff_phi_curr_times_phi[0] = data_ptr->quad.diff_phi_curr_times_phi.prev_integ;
    data_ptr->integrals.diff_phi_curr_times_phi[1] = data_ptr->quad.diff_phi_curr_times_phi.curr_integ;
    data_ptr->integrals.diff_phi_curr_times_phi[2] = data_ptr->quad.diff_phi_curr_times_phi.next_integ;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeIntegralsPhiCurrTimesDiffPhi(upProgramData<Type, N> & data_ptr) noexcept {
    data_ptr->integrals.phi_curr_times_diff_phi[0] = data_ptr->quad.phi_curr_times_diff_phi.prev_integ;
    data_ptr->integrals.phi_curr_times_diff_phi[1] = data_ptr->quad.phi_curr_times_diff_phi.curr_integ;
    data_ptr->integrals.phi_curr_times_diff_phi[2] = data_ptr->quad.phi_curr_times_diff_phi.next_integ;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeIntegralsPhiCurrTimesPhi(upProgramData<Type, N> & data_ptr) noexcept {
    data_ptr->integrals.phi_curr_times_phi[0] = data_ptr->quad.phi_curr_times_phi.prev_integ;
    data_ptr->integrals.phi_curr_times_phi[1] = data_ptr->quad.phi_curr_times_phi.curr_integ;
    data_ptr->integrals.phi_curr_times_phi[2] = data_ptr->quad.phi_curr_times_phi.next_integ;
}

template <std::floating_point Type, size_t N>
void ProgramData_computeIntegralsCoeffXX(upProgramData<Type, N> & data_ptr) noexcept {
    for(size_t idx = 0; idx < 3; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            auto & x_fact = data_ptr->integrals.diff_phi_curr_times_diff_phi[idx];
            auto & y_fact = data_ptr->integrals.phi_curr_times_phi[jdx];
            auto & result = data_ptr->integrals.coeff_xx[idx][jdx];
            
            result = x_fact * y_fact;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeIntegralsCoeffXY(upProgramData<Type, N> & data_ptr) noexcept {
    for(size_t idx = 0; idx < 3; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            auto & x_fact = data_ptr->integrals.diff_phi_curr_times_phi[idx];
            auto & y_fact = data_ptr->integrals.phi_curr_times_diff_phi[jdx];
            auto & result = data_ptr->integrals.coeff_xy[idx][jdx];
            
            result = 2.0f * x_fact * y_fact;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeIntegralsCoeffYY(upProgramData<Type, N> & data_ptr) noexcept {
    for(size_t idx = 0; idx < 3; ++idx){
        for(size_t jdx = 0; jdx < 3; ++jdx){
            auto & x_fact = data_ptr->integrals.phi_curr_times_phi[idx];
            auto & y_fact = data_ptr->integrals.diff_phi_curr_times_diff_phi[jdx];
            auto & result = data_ptr->integrals.coeff_yy[idx][jdx];
            
            result = x_fact * y_fact;
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_computeIntegrals(upProgramData<Type, N> & data_ptr) noexcept {
    ProgramData_computeIntegralsDiffPhiCurrTimesDiffPhi(data_ptr);
    ProgramData_computeIntegralsDiffPhiCurrTimesPhi(data_ptr);
    ProgramData_computeIntegralsPhiCurrTimesDiffPhi(data_ptr);
    ProgramData_computeIntegralsPhiCurrTimesPhi(data_ptr);
    ProgramData_computeIntegralsCoeffXX(data_ptr);
    ProgramData_computeIntegralsCoeffXY(data_ptr);
    ProgramData_computeIntegralsCoeffYY(data_ptr);
}