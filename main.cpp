#ifndef MAX_N
#define MAX_N 100
#endif

#include "read_inputs.hpp"
#include "subroutines.hpp"
#include "test.hpp"
#include <memory>

auto data_ptr = std::make_unique<ProgramData<double, MAX_N>>();

int main(){    
    ProgramData_readInputs(data_ptr);

    ProgramData_compute(data_ptr);
    
    ProgramData_displayResults(data_ptr);
    
    return 0;
}

