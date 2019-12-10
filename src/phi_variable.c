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
    String type_str = String_init("NULL");

    if (var.type == PhiType_OBJ) type_str = String_init("OBJ");
    if (var.type == PhiType_STR) type_str = String_init("STR");
    if (var.type == PhiType_NUM) type_str = String_init("NUM");
    if (var.type == PhiType_LIST) type_str = String_init("LIST");

    printf("<PhiVariable name=%s, type=%s, value=%s>\n", var.name.v, type_str.v, var.value.v);
}
