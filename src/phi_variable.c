#include "phi_variable.h"


PhiVariable PhiVariable_init(String name, PhiType type, String value) 
{
    PhiVariable var;
    var.name = name;
    var.type = type;
    var.value = value;
    return var;
}
