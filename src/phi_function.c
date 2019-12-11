#include "phi_function.h"


PhiFunction PhiFunction_init(String name) 
{
    PhiFunction func;
    func.name = name;
    func.body = String_init("");
    func.parameters = StringList_init();
    func.is_built_in = false;
    return func;
}

PhiFunction PhiFunction_from_body(String body)
{
    PhiFunction func = PhiFunction_init(String_init(""));
    StringList parameters = StringList_init("");
    String name = String_init("");
    String func_body = String_init("");
    String current_parameter = String_init("");
    bool in_func_name = true;
    bool in_parameter_field = false;
    bool in_func_body = false;

    for (unsigned int i = 0; i < strlen(body.v); i++)
    {
        if (body.v[i] == '(')
        {
            in_func_name = false;
            in_parameter_field = true;
            continue;
        }

        if (body.v[i] == ')')
        {
            // Add the last parameter
            if (strlen(current_parameter.v) > 0)
            {
                StringList_append(&parameters, current_parameter);
                String_clear(&current_parameter);
            }
            in_parameter_field = false;
            continue;
        }

        if (in_parameter_field)
        {
            if (body.v[i] == ',')
            {
                StringList_append(&parameters, current_parameter);
                String_clear(&current_parameter);
                continue;
            }

            String_appendc(&current_parameter, body.v[i]);
            continue;
        }

        if (in_func_name) 
        {
            String_appendc(&name, body.v[i]);
        }

        if (body.v[i] == '{')
        {
            in_func_body = true;
            continue;
        }

        if (body.v[i] == '}')
        {
            in_func_body = false;
        }

        if (in_func_body)
        {
            String_appendc(&func_body, body.v[i]);
        }
    }

    func.name = name;
    func.body = func_body;
    func.parameters = parameters;
    func.is_built_in = false;
    return func;
}

void PhiFunction_print(PhiFunction func)
{
    String params_str = String_init("");

    for (unsigned int i = 0; i < func.parameters.length; i++)
    {
        String_appends(&params_str, *StringList_at(func.parameters, i));
        String_appendc(&params_str, ',');
    }

    printf("<PhiFunction name=%s, params=%s, body=%s>\n", func.name.v, params_str.v, func.body.v);
}
