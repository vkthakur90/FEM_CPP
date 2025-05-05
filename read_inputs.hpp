#pragma once

#include "program_data.hpp"
#include "utils.hpp"
#include <memory>
#include <map>
#include <string>  

template <std::floating_point Type, size_t N>
void ProgramData_readInputsBulk(upProgramData<Type, N> & data_ptr, std::map<std::string, Type> & map) {
    #pragma omp parallel for simd collapse(2) schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & kxx = data_ptr->bulk_property.k_xx[idx][jdx];
            auto & kxy = data_ptr->bulk_property.k_xy[idx][jdx];
            auto & kyy = data_ptr->bulk_property.k_yy[idx][jdx];
            auto & q_rate = data_ptr->bulk_property.q_rate[idx][jdx];
            
            kxx = map["k_xx"];
            kxy = map["k_xy"];
            kyy = map["k_yy"];
            q_rate = map["q_rate"];
        }
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_readInputsBoundary(upProgramData<Type, N> & data_ptr, std::map<std::string, Type> & map) {
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & ref_top = data_ptr->boundary.top[idx];
        auto & ref_bottom = data_ptr->boundary.bottom[idx];
        auto & ref_left = data_ptr->boundary.left[idx];
        auto & ref_right = data_ptr->boundary.right[idx];
        
        ref_top = map["top"];
        ref_bottom = map["bottom"];
        ref_left = map["left"];
        ref_right = map["right"];
    }
}

template <std::floating_point Type, size_t N>
void ProgramData_displayResults(upProgramData<Type, N> & data_ptr, const char* filename){
    auto file = make_unique_file(filename, "w");
    
    for(size_t idx = 0; idx < data_ptr->size ; ++idx){
        for(size_t jdx = 0; jdx < data_ptr->size; ++jdx){
            auto & ref_x = data_ptr->grid.x[idx][jdx];
            auto & ref_y = data_ptr->grid.y[idx][jdx];
            auto & ref_T = data_ptr->conj_grad.x[idx][jdx];
            std::fprintf(
                file.get(),
                "%f\t%f\t\t%f\n",
                ref_x, ref_y, ref_T 
            );
        }
        std::fprintf(file.get(), "\n");
    }       
}

template <std::floating_point Type, size_t N>
void ProgramData_readInputs(upProgramData<Type, N> & data_ptr, std::map<std::string, Type> & map) {
    ProgramData_readInputsBulk(data_ptr, map);
    ProgramData_readInputsBoundary(data_ptr, map);
}