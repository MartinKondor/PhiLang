#include "phi_variable.h"


PhiVariable PhiVariable_init(String name, PhiType type, String value) 
{
    PhiVariable var;
    var.name = name;
    var.type = type;
    var.value = value;
    return var;
}

void PhiVariable_print(PhiVariable var)
{
    printf("<PhiVariable name=%s, type=%u, value=%s>\n", var.name, var.type, var.value);
}
