#ifndef MAX_N
#define MAX_N 100
#endif

#include "read_inputs.hpp"
#include "subroutines.hpp"
#include <memory>

#ifdef DEBUG
#include "test/test.hpp"
#endif



int main(){
    auto data_ptr = std::make_unique<ProgramData<double, MAX_N>>();
    
    ProgramData_readInputs(data_ptr);

    ProgramData_compute(data_ptr);
    
    ProgramData_displayResults(data_ptr);
    
    return 0;
}

