#pragma once

#include "program_data.hpp"
#include <cstdio>

template <size_t N>
void ProgramData_displayQuad(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    std::printf("integ D(phi_curr) x D(phi_prev) = %f\n", data_ptr->quad.diff_phi_curr_times_diff_phi.prev_integ);
    std::printf("integ D(phi_curr) x D(phi_curr) = %f\n", data_ptr->quad.diff_phi_curr_times_diff_phi.curr_integ);
    std::printf("integ D(phi_curr) x D(phi_next) = %f\n", data_ptr->quad.diff_phi_curr_times_diff_phi.next_integ);
    std::printf("\n");
    
    std::printf("integ D(phi_curr) x (phi_prev) = %f\n", data_ptr->quad.diff_phi_curr_times_phi.prev_integ);
    std::printf("integ D(phi_curr) x (phi_curr) = %f\n", data_ptr->quad.diff_phi_curr_times_phi.curr_integ);
    std::printf("integ D(phi_curr) x (phi_next) = %f\n", data_ptr->quad.diff_phi_curr_times_phi.next_integ);
    std::printf("\n");
    
    std::printf("integ (phi_curr) x D(phi_prev) = %f\n", data_ptr->quad.phi_curr_times_diff_phi.prev_integ);
    std::printf("integ (phi_curr) x D(phi_curr) = %f\n", data_ptr->quad.phi_curr_times_diff_phi.curr_integ);
    std::printf("integ (phi_curr) x D(phi_next) = %f\n", data_ptr->quad.phi_curr_times_diff_phi.next_integ);
    std::printf("\n");
    
    std::printf("integ (phi_curr) x (phi_prev) = %f\n", data_ptr->quad.phi_curr_times_phi.prev_integ);
    std::printf("integ (phi_curr) x (phi_curr) = %f\n", data_ptr->quad.phi_curr_times_phi.curr_integ);
    std::printf("integ (phi_curr) x (phi_next) = %f\n", data_ptr->quad.phi_curr_times_phi.next_integ);
    std::printf("\n");
}

template <size_t N>
void ProgramData_displayPhi(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    for(size_t idx = 0; idx < 2001; ++idx){
        std::printf(
            "%f\t\t%f\t%f\t%f\t\t%f\t%f\t%f\t\t%f\t%f\t%f\n",
            data_ptr->quad.u[idx][1],
            data_ptr->quad.phi.prev[idx][0],
            data_ptr->quad.phi.prev[idx][1],
            data_ptr->quad.phi.prev[idx][2],
            data_ptr->quad.phi.curr[idx][0],
            data_ptr->quad.phi.curr[idx][1],
            data_ptr->quad.phi.curr[idx][2],
            data_ptr->quad.phi.next[idx][0],
            data_ptr->quad.phi.next[idx][1],
            data_ptr->quad.phi.next[idx][2]
        );
    }
}

template <size_t N>
void ProgramData_displayPhiCurrTimesPhi(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    for(size_t idx = 0; idx < 2001; ++idx){
        std::printf(
            "%f\t\t%f\t%f\t%f\t\t%f\t%f\t%f\t\t%f\t%f\t%f\n",
            data_ptr->quad.u[idx][1],
            data_ptr->quad.phi_curr_times_phi.prev[idx][0],
            data_ptr->quad.phi_curr_times_phi.prev[idx][1],
            data_ptr->quad.phi_curr_times_phi.prev[idx][2],
            data_ptr->quad.phi_curr_times_phi.curr[idx][0],
            data_ptr->quad.phi_curr_times_phi.curr[idx][1],
            data_ptr->quad.phi_curr_times_phi.curr[idx][2],
            data_ptr->quad.phi_curr_times_phi.next[idx][0],
            data_ptr->quad.phi_curr_times_phi.next[idx][1],
            data_ptr->quad.phi_curr_times_phi.next[idx][2]
        );
    }
}
