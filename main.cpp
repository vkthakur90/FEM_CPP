#include "subroutines.hpp"
#include <memory>

int main(){
    auto data_ptr = std::make_unique<ProgramData<10>>();
    
    ProgramData_computeQuad(data_ptr);
    ProgramData_displayPhiCurrTimesPhi(data_ptr);
    return 0;
}

