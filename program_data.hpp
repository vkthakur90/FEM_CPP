#pragma once

#define SIMD_SIZE 512
#define SIMPSON_SIZE 20001

#include <cstddef>

template <size_t N>
struct ProgramData {
    size_t size{N};
    
    struct {
        float length_x{1.0};
        float length_y{1.0};
    } sim_box;
    
    struct {
        alignas(SIMD_SIZE/alignof(float)) float x[N][N]{};
        alignas(SIMD_SIZE/alignof(float)) float y[N][N]{};
        float delta_x{0.0f};
        float delta_y{0.0f};
    } grid;
    
    struct {
        alignas(SIMD_SIZE/alignof(float)) float q_rate[N][N]{1.0f};
        alignas(SIMD_SIZE/alignof(float)) float k_xx[N][N]{1.0f};
        alignas(SIMD_SIZE/alignof(float)) float k_xy[N][N]{0.0f};
        alignas(SIMD_SIZE/alignof(float)) float k_yy[N][N]{1.0f}; 
    } bulk_property;
    
    struct {
        alignas(SIMD_SIZE/alignof(float)) float top[N]{0.0f};
        alignas(SIMD_SIZE/alignof(float)) float bottom[N]{0.0f};
        alignas(SIMD_SIZE/alignof(float)) float left[N]{0.0f};
        alignas(SIMD_SIZE/alignof(float)) float right[N]{0.0f};
    } boundary;
    
    struct {
        alignas(SIMD_SIZE/alignof(float)) float u[SIMPSON_SIZE][3]{};
        
        struct {
           alignas(SIMD_SIZE/alignof(float)) float curr[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(float)) float prev[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(float)) float next[SIMPSON_SIZE][3]{};
        } phi;
        
        struct {
            alignas(SIMD_SIZE/alignof(float)) float curr[SIMPSON_SIZE]{};
            alignas(SIMD_SIZE/alignof(float)) float prev[SIMPSON_SIZE]{};
            alignas(SIMD_SIZE/alignof(float)) float next[SIMPSON_SIZE]{};
        } diff_phi;
        
        struct {
           alignas(SIMD_SIZE/alignof(float)) float curr[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(float)) float prev[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(float)) float next[SIMPSON_SIZE][3]{};
           float curr_integ;
           float prev_integ;
           float next_integ;
        } diff_phi_curr_times_diff_phi;
        
        struct {
           alignas(SIMD_SIZE/alignof(float)) float curr[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(float)) float prev[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(float)) float next[SIMPSON_SIZE][3]{};
           float curr_integ;
           float prev_integ;
           float next_integ;
        } diff_phi_curr_times_phi;
        
        struct {
           alignas(SIMD_SIZE/alignof(float)) float curr[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(float)) float prev[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(float)) float next[SIMPSON_SIZE][3]{};
           float curr_integ;
           float prev_integ;
           float next_integ;
        } phi_curr_times_diff_phi;
        
        struct {
           alignas(SIMD_SIZE/alignof(float)) float curr[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(float)) float prev[SIMPSON_SIZE][3]{};
           alignas(SIMD_SIZE/alignof(float)) float next[SIMPSON_SIZE][3]{};
           float curr_integ;
           float prev_integ;
           float next_integ;
        } phi_curr_times_phi;
        
        alignas(SIMD_SIZE/alignof(float)) float simpson[SIMPSON_SIZE]{};
    } quad;
    
    struct {
        float diff_phi_curr_times_diff_phi[3]{};
        float diff_phi_curr_times_phi[3]{};
        float phi_curr_times_diff_phi[3]{};
        float phi_curr_times_phi[3]{};
        
        float coeff_xx[3][3];
        float coeff_xy[3][3];
        float coeff_yy[3][3];
    } integrals;
    
    struct {
        alignas(SIMD_SIZE/alignof(float)) float mat_xx[N][N][3][3]{};
        alignas(SIMD_SIZE/alignof(float)) float mat_xy[N][N][3][3]{};
        alignas(SIMD_SIZE/alignof(float)) float mat_yy[N][N][3][3]{};
        alignas(SIMD_SIZE/alignof(float)) float mat[N][N][3][3]{};
        alignas(SIMD_SIZE/alignof(float)) float gen_rate[N][N]{};
    } discretized;
    
    struct {
        alignas(SIMD_SIZE/alignof(float)) float mat[N*N][N*N]{0.0f};
        alignas(SIMD_SIZE/alignof(float)) float heat_gen[N*N]{0.0f};
        alignas(SIMD_SIZE/alignof(float)) float soln[N*N]; 
    } lin_alg_solve;   
};