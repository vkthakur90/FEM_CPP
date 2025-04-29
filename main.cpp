#ifndef MAX_N
#define MAX_N 10
#endif

#include "subroutines.hpp"
#include <memory>

int main(){
    auto data_ptr = std::make_unique<ProgramData<MAX_N>>();
    
    ProgramData_computeQuad(data_ptr);
    ProgramData_computeIntegrals(data_ptr);
    ProgramData_computeGrid(data_ptr);
    ProgramData_computeDescretized(data_ptr);
    
    return 0;
}

