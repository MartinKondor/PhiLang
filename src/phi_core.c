#include "phi_core.h"


PhiStack Phi_eval(String code, unsigned int stack_id) 
{
    bool in_string = false;
    bool in_one_line_comment = false;
    bool in_function_def = false;
    String command = String_init("");
    unsigned int ch_index = 0;
    unsigned int ln_index = 1;
    PhiStack main_stack = PhiStack_init(stack_id);
    char ch;

    for (unsigned int i = 0; i < strlen(code.v); i++) 
    {
        ch = code.v[i];

        if (ch == '\n') 
        {
            ln_index++;
            if (in_one_line_comment)
            {
                in_one_line_comment = false;
            }
            continue;
        }

        if (in_one_line_comment || (ch == ' ' && !in_string)) 
        {
            continue;
        }

        if (ch == '#')
        {
            in_one_line_comment = true;
            continue;
        }
        
        if (ch == '"')
        {
            in_string = !in_string;
        }
        
        if (in_string)
        {
            String_appendc(&command, ch);
            continue;
        }

        if (ch == '{') 
        {
            in_function_def = true;
            continue;
        }

        if (ch == '}') 
        {
            if (!in_function_def) 
            {
                PhiError_print(PhiError_init("Unopened function definition.", ln_index, ch_index));
                exit(1);
            }

            in_function_def = false;
            String_clear(&command);
            continue;
        }

        if (in_function_def)
        {
            String_appendc(&command, ch);
            continue; 
        }

        if (ch == '!') 
        {
            if (in_string) 
            {
                PhiError_print(PhiError_init("Unclosed string.", ln_index, ch_index));
                exit(1);
            }

            String_clear(&command);
            continue;
        }

        String_appendc(&command, ch);
    }

    return main_stack;
}
