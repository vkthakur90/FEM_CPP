#pragma once

#include "../program_data.hpp"
#include "../utils.hpp"

template <std::floating_point Type, size_t N>
void ProgramData_displayQuad(upProgramData<Type, N> & data_ptr) {
    auto file = make_unique_file("outputs/quad_out.txt", "w");
    
    std::fprintf(file.get(), "integ D(phi_curr) x D(phi_prev) = %f\n", data_ptr->quad.diff_phi_curr_times_diff_phi.prev_integ);
    std::fprintf(file.get(), "integ D(phi_curr) x D(phi_curr) = %f\n", data_ptr->quad.diff_phi_curr_times_diff_phi.curr_integ);
    std::fprintf(file.get(), "integ D(phi_curr) x D(phi_next) = %f\n", data_ptr->quad.diff_phi_curr_times_diff_phi.next_integ);
    std::fprintf(file.get(), "\n");
    
    std::fprintf(file.get(), "integ D(phi_curr) x (phi_prev) = %f\n", data_ptr->quad.diff_phi_curr_times_phi.prev_integ);
    std::fprintf(file.get(), "integ D(phi_curr) x (phi_curr) = %f\n", data_ptr->quad.diff_phi_curr_times_phi.curr_integ);
    std::fprintf(file.get(), "integ D(phi_curr) x (phi_next) = %f\n", data_ptr->quad.diff_phi_curr_times_phi.next_integ);
    std::fprintf(file.get(), "\n");
    
    std::fprintf(file.get(), "integ (phi_curr) x D(phi_prev) = %f\n", data_ptr->quad.phi_curr_times_diff_phi.prev_integ);
    std::fprintf(file.get(), "integ (phi_curr) x D(phi_curr) = %f\n", data_ptr->quad.phi_curr_times_diff_phi.curr_integ);
    std::fprintf(file.get(), "integ (phi_curr) x D(phi_next) = %f\n", data_ptr->quad.phi_curr_times_diff_phi.next_integ);
    std::fprintf(file.get(), "\n");
    
    std::fprintf(file.get(), "integ (phi_curr) x (phi_prev) = %f\n", data_ptr->quad.phi_curr_times_phi.prev_integ);
    std::fprintf(file.get(), "integ (phi_curr) x (phi_curr) = %f\n", data_ptr->quad.phi_curr_times_phi.curr_integ);
    std::fprintf(file.get(), "integ (phi_curr) x (phi_next) = %f\n", data_ptr->quad.phi_curr_times_phi.next_integ);
    std::fprintf(file.get(), "\n");
}

template <std::floating_point Type, size_t N>
void ProgramData_displayPhi(upProgramData<Type, N> & data_ptr) {
    auto file = make_unique_file("outputs/quad_phi_out.txt", "w");
    
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        std::fprintf(
            file.get(),
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

template <std::floating_point Type, size_t N>
void ProgramData_displayDiffPhi(upProgramData<Type, N> & data_ptr) {
    auto file = make_unique_file("outputs/quad_diff_phi_out.txt", "w");
    
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        std::fprintf(
            file.get(),
            "%f\t\t%f\t\t%f\t\t%f\n",
            data_ptr->quad.u[idx][1],
            data_ptr->quad.diff_phi.prev[idx],
            data_ptr->quad.diff_phi.curr[idx],
            data_ptr->quad.diff_phi.next[idx]
        );
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_displayPhiCurrTimesPhi(upProgramData<Type, N> & data_ptr) {
    auto file = make_unique_file("outputs/quad_phi_times_phi_out.txt", "w");
    
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        std::fprintf(
            file.get(),
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

template <std::floating_point Type, size_t N>
void ProgramData_displayDiffPhiCurrTimesPhi(upProgramData<Type, N> & data_ptr) {
    auto file = make_unique_file("outputs/quad_diff_phi_times_phi_out.txt", "w");
    
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        std::fprintf(
            file.get(),
            "%f\t\t%f\t%f\t%f\t\t%f\t%f\t%f\t\t%f\t%f\t%f\n",
            data_ptr->quad.u[idx][1],
            data_ptr->quad.diff_phi_curr_times_phi.prev[idx][0],
            data_ptr->quad.diff_phi_curr_times_phi.prev[idx][1],
            data_ptr->quad.diff_phi_curr_times_phi.prev[idx][2],
            data_ptr->quad.diff_phi_curr_times_phi.curr[idx][0],
            data_ptr->quad.diff_phi_curr_times_phi.curr[idx][1],
            data_ptr->quad.diff_phi_curr_times_phi.curr[idx][2],
            data_ptr->quad.diff_phi_curr_times_phi.next[idx][0],
            data_ptr->quad.diff_phi_curr_times_phi.next[idx][1],
            data_ptr->quad.diff_phi_curr_times_phi.next[idx][2]
        );
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_displayPhiCurrTimesDiffPhi(upProgramData<Type, N> & data_ptr) {
    auto file = make_unique_file("outputs/quad_phi_times_diff_phi_out.txt", "w");
    
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        std::fprintf(
            file.get(),
            "%f\t\t%f\t%f\t%f\t\t%f\t%f\t%f\t\t%f\t%f\t%f\n",
            data_ptr->quad.u[idx][1],
            data_ptr->quad.phi_curr_times_diff_phi.prev[idx][0],
            data_ptr->quad.phi_curr_times_diff_phi.prev[idx][1],
            data_ptr->quad.phi_curr_times_diff_phi.prev[idx][2],
            data_ptr->quad.phi_curr_times_diff_phi.curr[idx][0],
            data_ptr->quad.phi_curr_times_diff_phi.curr[idx][1],
            data_ptr->quad.phi_curr_times_diff_phi.curr[idx][2],
            data_ptr->quad.phi_curr_times_diff_phi.next[idx][0],
            data_ptr->quad.phi_curr_times_diff_phi.next[idx][1],
            data_ptr->quad.phi_curr_times_diff_phi.next[idx][2]
        );
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_displayDiffPhiCurrTimesDiffPhi(upProgramData<Type, N> & data_ptr) {
    auto file = make_unique_file("outputs/quad_diff_phi_times_diff_phi_out.txt", "w");
    
    for(size_t idx = 0; idx < SIMPSON_SIZE; ++idx){
        std::fprintf(
            file.get(),
            "%f\t\t%f\t%f\t%f\t\t%f\t%f\t%f\t\t%f\t%f\t%f\n",
            data_ptr->quad.u[idx][1],
            data_ptr->quad.diff_phi_curr_times_diff_phi.prev[idx][0],
            data_ptr->quad.diff_phi_curr_times_diff_phi.prev[idx][1],
            data_ptr->quad.diff_phi_curr_times_diff_phi.prev[idx][2],
            data_ptr->quad.diff_phi_curr_times_diff_phi.curr[idx][0],
            data_ptr->quad.diff_phi_curr_times_diff_phi.curr[idx][1],
            data_ptr->quad.diff_phi_curr_times_diff_phi.curr[idx][2],
            data_ptr->quad.diff_phi_curr_times_diff_phi.next[idx][0],
            data_ptr->quad.diff_phi_curr_times_diff_phi.next[idx][1],
            data_ptr->quad.diff_phi_curr_times_diff_phi.next[idx][2]
        );
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_displayIntegrals(upProgramData<Type, N> & data_ptr) {
    auto file = make_unique_file("outputs/integrals_out.txt", "w");
    
    std::fprintf(file.get(), "\n\nCoeff XX\n");
    for(size_t idx = 0; idx < 3; ++idx){
        std::fprintf(file.get(), "i_%d", idx);
        for(size_t jdx = 0; jdx < 3; ++jdx){
            std::fprintf(file.get(), "\t%f", data_ptr->integrals.coeff_xx[idx][jdx]);
        }
        std::fprintf(file.get(), "\n");
    }
    
    std::fprintf(file.get(), "\n\nCoeff XY\n");
    for(size_t idx = 0; idx < 3; ++idx){
        std::fprintf(file.get(), "i_%d", idx);
        for(size_t jdx = 0; jdx < 3; ++jdx){
            std::fprintf(file.get(), "\t%f", data_ptr->integrals.coeff_xy[idx][jdx]);
        }
        std::fprintf(file.get(), "\n");
    }
    
    std::fprintf(file.get(), "\n\nCoeff YY\n");
    for(size_t idx = 0; idx < 3; ++idx){
        std::fprintf(file.get(), "i_%d", idx);
        for(size_t jdx = 0; jdx < 3; ++jdx){
            std::fprintf(file.get(), "\t%f", data_ptr->integrals.coeff_yy[idx][jdx]);
        }
        std::fprintf(file.get(), "\n");
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_displayLinAlgSolveMat(upProgramData<Type, N> & data_ptr) {
    auto file = make_unique_file("outputs/lin_alg_solve_mat_out.txt", "w");
    
    auto & NUM = data_ptr->size;
    for(size_t idx = 0; idx < NUM * NUM; ++idx){
        for(size_t jdx = 0; jdx < NUM * NUM; ++jdx){
            auto & result = data_ptr->lin_alg_solve.mat[idx][jdx];
            std::fprintf(file.get(), "%d\t%d\t\t%f\n", idx, jdx, result);
        }
        std::fprintf(file.get(), "\n");
    }    
}

template <std::floating_point Type, size_t N>
void ProgramData_displayBulkPropertyConductivity(upProgramData<Type, N> & data_ptr) {
    auto file = make_unique_file("outputs/bulk_property_k.txt", "w");
    
    auto & NUM = data_ptr->size;
    for(size_t idx = 0; idx < NUM; ++idx){
        for(size_t jdx = 0; jdx < NUM; ++jdx){
            auto & ref_kxx = data_ptr->bulk_property.k_xx[idx][jdx];
            auto & ref_kxy = data_ptr->bulk_property.k_xy[idx][jdx];
            auto & ref_kyy = data_ptr->bulk_property.k_yy[idx][jdx];
            std::fprintf(file.get(), "%d\t%d\t\t%f\t%f\t%f\n", idx, jdx, 
                         ref_kxx, ref_kxy, ref_kyy);
        }
        std::fprintf(file.get(), "\n");
    }    
}

template <std::floating_point Type, size_t N>
void ProgramData_displayDiscretizedMat(upProgramData<Type, N> & data_ptr) {
    auto file = make_unique_file("outputs/discretized_mat.txt", "w");

    for(size_t idx = 0; idx < data_ptr->size ; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            for(size_t mdx = 0; mdx < 3; ++mdx){
                for(size_t ndx = 0; ndx < 3; ++ndx){
                    auto & ref_mat_xx = data_ptr->discretized.mat_xx[idx][jdx][mdx][ndx];
                    auto & ref_mat_xy = data_ptr->discretized.mat_xy[idx][jdx][mdx][ndx];
                    auto & ref_mat_yy = data_ptr->discretized.mat_yy[idx][jdx][mdx][ndx];
                    auto & ref_mat = data_ptr->discretized.mat[idx][jdx][mdx][ndx];
                    std::fprintf(
                        file.get(),
                        "%d\t%d\t%d\t%d\t\t%f\t%f\t%f\t%f\n",
                        idx, jdx, mdx, ndx, 
                        ref_mat_xx, ref_mat_xy, ref_mat_yy, ref_mat
                    );
                }
            }
            std::fprintf(file.get(), "\n");
        }
    }        
}

template <std::floating_point Type, size_t N>
void ProgramData_displayConjGradA(upProgramData<Type, N> & data_ptr){
    auto file = make_unique_file("outputs/conj_grad_A.txt", "w");

    for(size_t idx = 0; idx < data_ptr->size ; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            for(size_t mdx = 0; mdx < 3; ++mdx){
                for(size_t ndx = 0; ndx < 3; ++ndx){
                    auto & ref_A = data_ptr->discretized.mat[idx][jdx][mdx][ndx];
                    std::fprintf(
                        file.get(),
                        "%d\t%d\t%d\t%d\t\t%f\n",
                        idx, jdx, mdx, ndx, 
                        ref_A
                    );
                }
            }
            std::fprintf(file.get(), "\n");
        }
    }        
}

template <std::floating_point Type, size_t N>
void ProgramData_displayConjGradB(upProgramData<Type, N> & data_ptr){
    auto file = make_unique_file("outputs/conj_grad_b.txt", "w");
    
    for(size_t idx = 0; idx < data_ptr->size ; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_x = data_ptr->conj_grad.b[idx][jdx];
            std::fprintf(
                file.get(),
                "%d\t%d\t\t%f\n",
                idx, jdx, ref_x 
            );
        }
        std::fprintf(file.get(), "\n");
    }       
}

template <std::floating_point Type, size_t N>
void ProgramData_displayConjGradY(upProgramData<Type, N> & data_ptr){
    auto file = make_unique_file("outputs/conj_grad_y.txt", "w");
    
    for(size_t idx = 0; idx < data_ptr->size ; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_y = data_ptr->conj_grad.y[idx][jdx];
            std::fprintf(
                file.get(),
                "%d\t%d\t\t%f\n",
                idx, jdx, ref_y 
            );
        }
        std::fprintf(file.get(), "\n");
    }       
}

template <std::floating_point Type, size_t N>
void ProgramData_displayConjGradR(upProgramData<Type, N> & data_ptr){
    auto file = make_unique_file("outputs/conj_grad_r.txt", "w");
    
    for(size_t idx = 0; idx < data_ptr->size ; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_r = data_ptr->conj_grad.r[idx][jdx];
            std::fprintf(
                file.get(),
                "%d\t%d\t\t%f\n",
                idx, jdx, ref_r 
            );
        }
        std::fprintf(file.get(), "\n");
    }       
}

template <std::floating_point Type, size_t N>
void ProgramData_displayConjGradP(upProgramData<Type, N> & data_ptr){
    auto file = make_unique_file("outputs/conj_grad_p.txt", "w");
    
    for(size_t idx = 0; idx < data_ptr->size ; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_p = data_ptr->conj_grad.p[idx][jdx];
            std::fprintf(
                file.get(),
                "%d\t%d\t\t%f\n",
                idx, jdx, ref_p 
            );
        }
        std::fprintf(file.get(), "\n");
    }       
}

template <std::floating_point Type, size_t N>
void ProgramData_displayConjGradX(upProgramData<Type, N> & data_ptr){
    auto file = make_unique_file("outputs/conj_grad_x.txt", "w");
    
    for(size_t idx = 0; idx < data_ptr->size ; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_x = data_ptr->conj_grad.x[idx][jdx];
            std::fprintf(
                file.get(),
                "%d\t%d\t\t%f\n",
                idx, jdx, ref_x 
            );
        }
        std::fprintf(file.get(), "\n");
    }       
}

template <std::floating_point Type, size_t N>
void ProgramData_displayConjGradQ(upProgramData<Type, N> & data_ptr){
    auto file = make_unique_file("outputs/conj_grad_q.txt", "w");
    
    for(size_t idx = 0; idx < data_ptr->size ; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_q = data_ptr->conj_grad.q[idx][jdx];
            std::fprintf(
                file.get(),
                "%d\t%d\t\t%f\n",
                idx, jdx, ref_q 
            );
        }
        std::fprintf(file.get(), "\n");
    }       
}

template <std::floating_point Type, size_t N>
void ProgramData_displayTests(upProgramData<Type, N> & data_ptr){
    ProgramData_displayPhi(data_ptr);
    ProgramData_displayDiffPhi(data_ptr);
    ProgramData_displayDiffPhiCurrTimesDiffPhi(data_ptr);
    ProgramData_displayDiffPhiCurrTimesPhi(data_ptr);
    ProgramData_displayPhiCurrTimesDiffPhi(data_ptr);
    ProgramData_displayPhiCurrTimesPhi(data_ptr);
    ProgramData_displayQuad(data_ptr);
    ProgramData_displayIntegrals(data_ptr);
    ProgramData_displayBulkPropertyConductivity(data_ptr);
    ProgramData_displayDiscretizedMat(data_ptr);
    ProgramData_displayConjGradX(data_ptr);
}
