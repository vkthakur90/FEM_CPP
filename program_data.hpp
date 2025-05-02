#pragma once

#define SIMD_SIZE 512
#define SIMPSON_SIZE 2001

#include "utils.hpp"

template <std::floating_point Type, size_t N>
struct ProgramData {
    size_t size{N};
    
    struct {
        Type length_x{1.0f};
        Type length_y{1.0f};
    } sim_box;
    
    struct {
        alignas(SIMD_SIZE/alignof(Type)) Type x[N][N]{};
        alignas(SIMD_SIZE/alignof(Type)) Type y[N][N]{};
        Type delta_x{0.0f};
        Type delta_y{0.0f};
    } grid;
    
    struct {
        alignas(SIMD_SIZE/alignof(Type)) Type q_rate[N][N]{};
        alignas(SIMD_SIZE/alignof(Type)) Type k_xx[N][N]{};
        alignas(SIMD_SIZE/alignof(Type)) Type k_xy[N][N]{};
        alignas(SIMD_SIZE/alignof(Type)) Type k_yy[N][N]{}; 
    } bulk_property;
    
    struct {
        alignas(SIMD_SIZE/alignof(Type)) Type top[N]{};
        alignas(SIMD_SIZE/alignof(Type)) Type bottom[N]{};
        alignas(SIMD_SIZE/alignof(Type)) Type left[N]{};
        alignas(SIMD_SIZE/alignof(Type)) Type right[N]{};
    } boundary;
    
    struct {
        ShapeFunction shape{QUINTIC};
        
        alignas(SIMD_SIZE/alignof(Type)) Type u[SIMPSON_SIZE][3]{};
        
        struct {
           alignas(SIMD_SIZE/alignof(Type)) Type curr[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(Type)) Type prev[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(Type)) Type next[SIMPSON_SIZE][3]{};
        } phi;
        
        struct {
            alignas(SIMD_SIZE/alignof(Type)) Type curr[SIMPSON_SIZE]{};
            alignas(SIMD_SIZE/alignof(Type)) Type prev[SIMPSON_SIZE]{};
            alignas(SIMD_SIZE/alignof(Type)) Type next[SIMPSON_SIZE]{};
        } diff_phi;
        
        struct {
           alignas(SIMD_SIZE/alignof(Type)) Type curr[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(Type)) Type prev[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(Type)) Type next[SIMPSON_SIZE][3]{};
           Type curr_integ;
           Type prev_integ;
           Type next_integ;
        } diff_phi_curr_times_diff_phi;
        
        struct {
           alignas(SIMD_SIZE/alignof(Type)) Type curr[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(Type)) Type prev[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(Type)) Type next[SIMPSON_SIZE][3]{};
           Type curr_integ;
           Type prev_integ;
           Type next_integ;
        } diff_phi_curr_times_phi;
        
        struct {
           alignas(SIMD_SIZE/alignof(Type)) Type curr[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(Type)) Type prev[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(Type)) Type next[SIMPSON_SIZE][3]{};
           Type curr_integ;
           Type prev_integ;
           Type next_integ;
        } phi_curr_times_diff_phi;
        
        struct {
           alignas(SIMD_SIZE/alignof(Type)) Type curr[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(Type)) Type prev[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(Type)) Type next[SIMPSON_SIZE][3]{};
           Type curr_integ;
           Type prev_integ;
           Type next_integ;
        } phi_curr_times_phi;
        
        alignas(SIMD_SIZE/alignof(Type)) Type simpson[SIMPSON_SIZE]{};
    } quad;
    
    struct {
        Type diff_phi_curr_times_diff_phi[3]{};
        Type diff_phi_curr_times_phi[3]{};
        Type phi_curr_times_diff_phi[3]{};
        Type phi_curr_times_phi[3]{};
        
        Type coeff_xx[3][3]{};
        Type coeff_xy[3][3]{};
        Type coeff_yy[3][3]{};
    } integrals;
    
    struct {
        alignas(SIMD_SIZE/alignof(Type)) Type mat_xx[N][N][3][3]{};
        alignas(SIMD_SIZE/alignof(Type)) Type mat_xy[N][N][3][3]{};
        alignas(SIMD_SIZE/alignof(Type)) Type mat_yy[N][N][3][3]{};
        alignas(SIMD_SIZE/alignof(Type)) Type mat[N][N][3][3]{};
        alignas(SIMD_SIZE/alignof(Type)) Type gen_rate[N][N]{};
    } discretized;
    
    struct {
        alignas(SIMD_SIZE/alignof(Type)) Type mat[N*N][N*N]{};
        alignas(SIMD_SIZE/alignof(Type)) Type heat_gen[N*N]{};
        alignas(SIMD_SIZE/alignof(Type)) Type soln[N*N]; 
    } lin_alg_solve;   
};