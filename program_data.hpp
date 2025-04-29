#pragma once

#define SIMD_SIZE 512

template <size_t N>
struct ProgramData {
    size_t size{N};
    
    struct {
        float k_xx[N][N]{};
        float k_xy[N][N]{};
        float k_yy[N][N]{};
    } conductivity_tensor; 
    
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
        alignas(SIMD_SIZE/alignof(float)) float q[N][N]{};
        alignas(SIMD_SIZE/alignof(float)) float T[N][N]{}; 
    } bulk_condition;
    
    struct {
        alignas(SIMD_SIZE/alignof(float)) float top[N]{};
        alignas(SIMD_SIZE/alignof(float)) float bottom[N]{};
        alignas(SIMD_SIZE/alignof(float)) float left[N]{};
        alignas(SIMD_SIZE/alignof(float)) float right[N]{};
    } boundary;
    
    struct {
        alignas(SIMD_SIZE/alignof(float)) float u[2001][3]{};
        
        struct {
           alignas(SIMD_SIZE/alignof(float)) float curr[2001][3]{};
           alignas(SIMD_SIZE/alignof(float)) float prev[2001][3]{};
           alignas(SIMD_SIZE/alignof(float)) float next[2001][3]{};
        } phi;
        
        struct {
            alignas(SIMD_SIZE/alignof(float)) float curr[2001]{};
            alignas(SIMD_SIZE/alignof(float)) float prev[2001]{};
            alignas(SIMD_SIZE/alignof(float)) float next[2001]{};
        } diff_phi;
        
        struct {
           alignas(SIMD_SIZE/alignof(float)) float curr[2001][3]{};
           alignas(SIMD_SIZE/alignof(float)) float prev[2001][3]{};
           alignas(SIMD_SIZE/alignof(float)) float next[2001][3]{};
           float curr_integ;
           float prev_integ;
           float next_integ;
        } diff_phi_curr_times_diff_phi;
        
        struct {
           alignas(SIMD_SIZE/alignof(float)) float curr[2001][3]{};
           alignas(SIMD_SIZE/alignof(float)) float prev[2001][3]{};
           alignas(SIMD_SIZE/alignof(float)) float next[2001][3]{};
           float curr_integ;
           float prev_integ;
           float next_integ;
        } diff_phi_curr_times_phi;
        
        struct {
           alignas(SIMD_SIZE/alignof(float)) float curr[2001][3]{};
           alignas(SIMD_SIZE/alignof(float)) float prev[2001][3]{};
           alignas(SIMD_SIZE/alignof(float)) float next[2001][3]{};
           float curr_integ;
           float prev_integ;
           float next_integ;
        } phi_curr_times_diff_phi;
        
        struct {
           alignas(SIMD_SIZE/alignof(float)) float curr[2001][3]{};
           alignas(SIMD_SIZE/alignof(float)) float prev[2001][3]{};
           alignas(SIMD_SIZE/alignof(float)) float next[2001][3]{};
           float curr_integ;
           float prev_integ;
           float next_integ;
        } phi_curr_times_phi;
        
        alignas(SIMD_SIZE/alignof(float)) float simpson[2001]{};
    } quad;
    
    struct {
        alignas(SIMD_SIZE/alignof(float)) float mat_xx[N][N][3][3]{};
        alignas(SIMD_SIZE/alignof(float)) float mat_xy[N][N][3][3]{};
        alignas(SIMD_SIZE/alignof(float)) float mat_yy[N][N][3][3]{};
        alignas(SIMD_SIZE/alignof(float)) float mat[N][N][3][3]{};
        alignas(SIMD_SIZE/alignof(float)) float heat_gen[N][N]{};
        float coeff_xx[3][3];
        float coeff_xy[3][3];
        float coeff_yy[3][3];
    } discretized;
    
    struct {
        alignas(SIMD_SIZE/alignof(float)) float mat[N*N][N*N]{};
        alignas(SIMD_SIZE/alignof(float)) float heat_gen[N*N]{};
        alignas(SIMD_SIZE/alignof(float)) float c[N*N]; 
    } solution;   
};