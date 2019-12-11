#include "phi_type.h"


PhiType PhiType_determine_type(String value) 
{
    if (value.v[0] == '"')
    {
        return PhiType_STR;
    }
    
    if (value.v[0] == '1' || value.v[0] == '2' || value.v[0] == '3' ||
        value.v[0] == '4' || value.v[0] == '5' || value.v[0] == '6' ||
        value.v[0] == '7' || value.v[0] == '8' || value.v[0] == '9' ||
        value.v[0] == '0' || strcmp(value.v, "true") == 0 || strcmp(value.v, "false") == 0)
    {
        return PhiType_NUM;
    }

    if (value.v[0] == '[')
    {
        return PhiType_LIST;
    }
    
    return PhiType_NULL;
}
