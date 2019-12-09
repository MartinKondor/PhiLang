#include "phi_function.h"


PhiFunction PhiFunction_init(String name) 
{
    PhiFunction func;
    func.name = name;
    func.body = String_init("");
    func.parameters = PhiVariableList_init();
    func.is_built_in = false;
    return func;
}

PhiFunction PhiFunction_from_body(String body)
{
    PhiFunction func = PhiFunction_init(String_init(""));
    func.body = body;
    return func;
}

void PhiFunction_print(PhiFunction func)
{
    printf("<PhiFunction name=%s, params=%u, body=%s>\n", func.name.v, func.parameters.length, func.body.v);
}
