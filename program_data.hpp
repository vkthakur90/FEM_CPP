#pragma once

#include <cstddef>
#include <concepts>
#include <memory>

constexpr size_t SIMD_SIZE = 512; 
constexpr size_t SIMPSON_SIZE = 2001;

enum ShapeFunction {
    LINEAR,
    CUBIC,
    QUINTIC    
};

template <std::floating_point Type>
struct SimBox {
    Type length_x{1.0f};
    Type length_y{1.0f};
};

template <std::floating_point Type, size_t N>
struct Grid {
    alignas(SIMD_SIZE/alignof(Type)) Type x[N][N]{};
    alignas(SIMD_SIZE/alignof(Type)) Type y[N][N]{};
    Type delta_x{0.0f};
    Type delta_y{0.0f};
};

template <std::floating_point Type, size_t N>
struct BulkProperty {
    alignas(SIMD_SIZE/alignof(Type)) Type q_rate[N][N]{};
    alignas(SIMD_SIZE/alignof(Type)) Type k_xx[N][N]{};
    alignas(SIMD_SIZE/alignof(Type)) Type k_xy[N][N]{};
    alignas(SIMD_SIZE/alignof(Type)) Type k_yy[N][N]{};     
};

template <std::floating_point Type, size_t N>
struct Boundary {
    alignas(SIMD_SIZE/alignof(Type)) Type top[N]{};
    alignas(SIMD_SIZE/alignof(Type)) Type bottom[N]{};
    alignas(SIMD_SIZE/alignof(Type)) Type left[N]{};
    alignas(SIMD_SIZE/alignof(Type)) Type right[N]{};
};

template <std::floating_point Type, size_t N>
struct ShapeFnTable {
    alignas(SIMD_SIZE/alignof(Type)) Type curr[N][3]{};
    alignas(SIMD_SIZE/alignof(Type)) Type prev[N][3]{};
    alignas(SIMD_SIZE/alignof(Type)) Type next[N][3]{};
};

template <std::floating_point Type, size_t N>
struct DiffShapeFnTable {
    alignas(SIMD_SIZE/alignof(Type)) Type curr[N]{};
    alignas(SIMD_SIZE/alignof(Type)) Type prev[N]{};
    alignas(SIMD_SIZE/alignof(Type)) Type next[N]{};
};

template <std::floating_point Type, size_t N>
struct ShapeFnInteg {
    alignas(SIMD_SIZE/alignof(Type)) Type curr[N][3]{};
    alignas(SIMD_SIZE/alignof(Type)) Type prev[N][3]{};
    alignas(SIMD_SIZE/alignof(Type)) Type next[N][3]{}; 
    Type curr_integ{};
    Type prev_integ{};
    Type next_integ{};
};

template <std::floating_point Type, size_t N>
struct Quad {
    ShapeFunction shape{LINEAR};
    
    alignas(SIMD_SIZE/alignof(Type)) Type u[SIMPSON_SIZE][3]{};
    alignas(SIMD_SIZE/alignof(Type)) Type simpson[SIMPSON_SIZE]{};
    
    ShapeFnTable<Type, N> phi{};
    DiffShapeFnTable<Type, N> diff_phi{};
    
    ShapeFnInteg<Type, N> diff_phi_curr_times_diff_phi{};
    ShapeFnInteg<Type, N> diff_phi_curr_times_phi{};
    ShapeFnInteg<Type, N> phi_curr_times_diff_phi{};
    ShapeFnInteg<Type, N> phi_curr_times_phi{};    
};

template <std::floating_point Type>
struct IntegralTables{
    Type diff_phi_curr_times_diff_phi[3]{};
    Type diff_phi_curr_times_phi[3]{};
    Type phi_curr_times_diff_phi[3]{};
    Type phi_curr_times_phi[3]{};
    
    Type coeff_xx[3][3]{};
    Type coeff_xy[3][3]{};
    Type coeff_yy[3][3]{}; 
};

template <std::floating_point Type, size_t N>
struct Discretized {
    alignas(SIMD_SIZE/alignof(Type)) Type mat_xx[N][N][3][3]{};
    alignas(SIMD_SIZE/alignof(Type)) Type mat_xy[N][N][3][3]{};
    alignas(SIMD_SIZE/alignof(Type)) Type mat_yy[N][N][3][3]{};
    alignas(SIMD_SIZE/alignof(Type)) Type mat[N][N][3][3]{};
    alignas(SIMD_SIZE/alignof(Type)) Type gen_rate[N][N]{};
};

template <std::floating_point Type, size_t N>
struct LinAlgSolve{
    alignas(SIMD_SIZE/alignof(Type)) Type mat[N*N][N*N]{};
    alignas(SIMD_SIZE/alignof(Type)) Type heat_gen[N*N]{};
    alignas(SIMD_SIZE/alignof(Type)) Type soln[N*N]; 
};

template <std::floating_point Type, size_t N>
struct ConjugateGradient {
    size_t max_iter{10};
    alignas(SIMD_SIZE/alignof(Type)) Type A[N][N][3][3]{};
    alignas(SIMD_SIZE/alignof(Type)) Type b[N][N]{};
    alignas(SIMD_SIZE/alignof(Type)) Type y[N][N]{};
    alignas(SIMD_SIZE/alignof(Type)) Type x[N][N]{};
    alignas(SIMD_SIZE/alignof(Type)) Type r[N][N]{};
    alignas(SIMD_SIZE/alignof(Type)) Type p[N][N]{};
    alignas(SIMD_SIZE/alignof(Type)) Type q[N][N]{};
    Type alpha{};
    Type beta{};
    Type tol{};
    Type r_dor_r{};
    Type next_r_dot_next_r{};
    Type p_dot_q{};
};

template <std::floating_point Type, size_t N>
struct ProgramData {
    size_t size{N};
    
    SimBox<Type> sim_box{};
    Grid<Type, N> grid{};
    
    BulkProperty<Type, N> bulk_property{};
    Boundary<Type, N> boundary{};
    
    Quad<Type, SIMPSON_SIZE> quad{};
    IntegralTables<Type> integrals{};
    
    Discretized<Type, N> discretized{};
    ConjugateGradient<Type, N> conj_grad{};
    
    LinAlgSolve<Type, N> lin_alg_solve{};
};

template <std::floating_point Type, size_t N>
using upProgramData = std::unique_ptr<ProgramData<Type, N>>;
