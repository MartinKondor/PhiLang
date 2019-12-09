#include "phi_function.h"


PhiFunction PhiFunction_init(String name) 
{
    PhiFunction func;
    func.name = name;
    func.parameters = PhiVariableList_init();
    func.is_built_in = false;
    return func;
}

void PhiFunction_print(PhiFunction func) 
{
    printf("<PhiFunction name=%s, params=%u>\n", func.name, func.parameters.length);
}
