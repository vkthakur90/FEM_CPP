#ifndef MAX_N
#define MAX_N 10
#endif

#include "read_inputs.hpp"
#include "subroutines.hpp"
#include "test.hpp"
#include <memory>

int main(){
    auto data_ptr = std::make_unique<ProgramData<float, MAX_N>>();
    
    ProgramData_readInputs(data_ptr);

    ProgramData_compute(data_ptr);
    
    ProgramData_displayTests(data_ptr);
    
    return 0;
}

