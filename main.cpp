#include "subroutines.hpp"
#include <memory>

int main(){
    auto data_ptr = std::make_unique<ProgramData<10>>();
    
    ProgramData_computeQuad(data_ptr);
    ProgramData_computeIntegrals(data_ptr);
    ProgramData_displayIntegrals(data_ptr);
    return 0;
}

