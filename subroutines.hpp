#pragma once

#include "program_data.hpp"
#include "grid.hpp"
#include "quad.hpp"
#include "integrals.hpp"
#include "discretized.hpp"
#include "lin_alg_solve_mat.hpp"
#include "conj_grad.hpp"

template <std::floating_point Type, size_t N>
void ProgramData_compute(upProgramData<Type, N> & data_ptr) noexcept {
    ProgramData_computeQuad(data_ptr);
    ProgramData_computeIntegrals(data_ptr);
    ProgramData_computeGrid(data_ptr);
    ProgramData_computeDescretized(data_ptr);
    //ProgramData_computeLinAlgSolveMat(data_ptr);
    ProgramData_computeConjGrad(data_ptr);
}

