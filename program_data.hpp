#pragma once

#define SIMD_SIZE 512

template <size_t N>
struct alignas(SIMD_SIZE) ProgramData {
    size_t size{N};
    
    struct {
        alignas(alignof(float)) float k_xx{0.0f};
        alignas(alignof(float)) float k_xy{0.0f};
        alignas(alignof(float)) float k_yy{0.0f};
    } cond; 
    
    struct {
        alignas(alignof(float)) float length_x{1.0};
        alignas(alignof(float)) float length_y{1.0};
    } sim_box;
    
    struct {
        alignas(SIMD_SIZE/alignof(float)) float x[N][N]{};
        alignas(SIMD_SIZE/alignof(float)) float y[N][N]{};
        alignas(SIMD_SIZE/alignof(float)) float q[N][N]{};
        alignas(SIMD_SIZE/alignof(float)) float T[N][N]{};
        alignas(alignof(float)) float delta_x{0.0f};
        alignas(alignof(float)) float delta_y{0.0f};
    } grid;
    
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
        } diff_phi_curr_times_diff_phi;
        
        struct {
           alignas(SIMD_SIZE/alignof(float)) float curr[2001][3]{};
           alignas(SIMD_SIZE/alignof(float)) float prev[2001][3]{};
           alignas(SIMD_SIZE/alignof(float)) float next[2001][3]{};
        } diff_phi_curr_times_phi;
        
        struct {
           alignas(SIMD_SIZE/alignof(float)) float curr[2001][3]{};
           alignas(SIMD_SIZE/alignof(float)) float prev[2001][3]{};
           alignas(SIMD_SIZE/alignof(float)) float next[2001][3]{};
        } phi_curr_times_diff_phi;
        
        struct {
           alignas(SIMD_SIZE/alignof(float)) float curr[2001][3]{};
           alignas(SIMD_SIZE/alignof(float)) float prev[2001][3]{};
           alignas(SIMD_SIZE/alignof(float)) float next[2001][3]{};
        } phi_times_phi;
        
        struct {
            alignas(alignof(float)) float diff_phi_curr_times_diff_phi{};
            alignas(alignof(float)) float diff_phi_curr_times_phi{};
            alignas(alignof(float)) float phi_curr_times_diff_phi{};
            alignas(alignof(float)) float phi_curr_times_phi{};
        } integ_curr;
        
        struct {
            alignas(alignof(float)) float diff_phi_curr_times_diff_phi{};
            alignas(alignof(float)) float diff_phi_curr_times_phi{};
            alignas(alignof(float)) float phi_curr_times_diff_phi{};
            alignas(alignof(float)) float phi_curr_times_phi{};
        } integ_prev;
        
        struct {
            alignas(alignof(float)) float diff_phi_curr_times_diff_phi{};
            alignas(alignof(float)) float diff_phi_curr_times_phi{};
            alignas(alignof(float)) float phi_curr_times_diff_phi{};
            alignas(alignof(float)) float phi_curr_times_phi{};
        } integ_next;
    } quad;
    
    struct {
        alignas(SIMD_SIZE/alignof(float)) float mat[N][N][3][3]{};
        alignas(SIMD_SIZE/alignof(float)) float heat_gen[N][N]{};
    } discretized;
    
    struct {
        alignas(SIMD_SIZE/alignof(float)) float mat[N*N][N*N]{};
        alignas(SIMD_SIZE/alignof(float)) float heat_gen[N*N]{};
        alignas(SIMD_SIZE/alignof(float)) float c[N*N]; 
    } solution;   
};