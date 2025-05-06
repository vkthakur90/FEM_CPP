#pragma once

#include "utils.hpp"
#include "subroutines.hpp"
#include <memory>
#include <map>
#include <functional>
#include <string>

template <std::floating_point Type, size_t N>
class FemSolver {
public:
    FemSolver() : data_ptr(std::make_unique<ProgramData<Type, N>>()) {}
    
    void set_length_x(Type val){
        data_ptr->sim_box.length_x = (val > 0) ? val : 1.0;
    }
    
    void set_length_y(Type val){
        data_ptr->sim_box.length_y = (val > 0) ? val : 1.0;
    }
    
    void set_k_xx(Type val){
        #pragma omp parallel for simd collapse(2) schedule(static)
        for(size_t idx = 0; idx < data_ptr->size; ++idx){
            for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
                auto & res = data_ptr->bulk_property.k_xx[idx][jdx];
                
                res = val;
            }
        }
    }
    
    void set_k_xy(Type val){
        #pragma omp parallel for simd collapse(2) schedule(static)
        for(size_t idx = 0; idx < data_ptr->size; ++idx){
            for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
                auto & res = data_ptr->bulk_property.k_xy[idx][jdx];
                
                res = val;
            }
        }
    }
    
    void set_k_yy(Type val){
        #pragma omp parallel for simd collapse(2) schedule(static)
        for(size_t idx = 0; idx < data_ptr->size; ++idx){
            for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
                auto & res = data_ptr->bulk_property.k_yy[idx][jdx];
                
                res = val;
            }
        }
    }
    
    void set_q_rate(Type val){
        #pragma omp parallel for simd collapse(2) schedule(static)
        for(size_t idx = 0; idx < data_ptr->size; ++idx){
            for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
                auto & res = data_ptr->bulk_property.q_rate[idx][jdx];
                
                res = val;
            }
        }
    }
    
    void set_boundary_top(Type val){
        #pragma omp parallel for simd schedule(static)
        for(size_t idx = 0; idx < data_ptr->size; ++idx){
            auto & res = data_ptr->boundary.top[idx];
            
            res = val;
        }
    }
    
    void set_boundary_bottom(Type val){
        #pragma omp parallel for simd schedule(static)
        for(size_t idx = 0; idx < data_ptr->size; ++idx){
            auto & res = data_ptr->boundary.bottom[idx];
            
            res = val;
        }
    }
    
    void set_boundary_left(Type val){
        #pragma omp parallel for simd schedule(static)
        for(size_t idx = 0; idx < data_ptr->size; ++idx){
            auto & res = data_ptr->boundary.left[idx];
            
            res = val;
        }
    }
    
    void set_boundary_right(Type val){
        #pragma omp parallel for simd schedule(static)
        for(size_t idx = 0; idx < data_ptr->size; ++idx){
            auto & res = data_ptr->boundary.right[idx];
            
            res = val;
        }
    }
    
    void compute() {
        ProgramData_compute(data_ptr);
    }    
    
    void write_to_file(const char * filename){
        auto file = make_unique_file(filename, "w");
        
        std::fprintf(file.get(), "X, Y, Z\n");
        for(size_t idx = 0; idx < data_ptr->size ; ++idx){
            for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
                auto & ref_x = data_ptr->grid.x[idx][jdx];
                auto & ref_y = data_ptr->grid.y[idx][jdx];
                auto & ref_T = data_ptr->conj_grad.x[idx][jdx];
                std::fprintf(
                    file.get(),
                    "%f, %f, %f\n",
                    ref_x, ref_y, ref_T 
                );
            }
            std::fprintf(file.get(), "\n");
        }       
    }
    
private:
    std::unique_ptr<ProgramData<Type, N>> data_ptr{nullptr};
};