#include "phi.h"
#include "phi_error.h"


int main(const int argc, const char** argv)
{
    if (argc != 2)
    {
        printf("No input file provided.\nProcess terminated.\n");
        exit(1);
    }

    FILE* input_file = fopen(argv[1], "r");

    if (input_file == NULL)
    {
        printf("Input file cannot be opened.\nProcess terminated.\n");
        exit(1);
    }

    bool in_string = false;
    bool in_one_line_comment = false;
    bool in_function_def = false;
    String command = String_init("");
    unsigned int ch_index = 0;
    unsigned int ln_index = 1;
    char ch;
    // main_stack = PhiStack()
    // main_stack.id = stack_id
    // Phi_setup_stack(main_stack)

    do 
    {
        ch = fgetc(input_file);

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

            String_clear(&command);
            continue;
        }

        if (in_function_def)
        {
            String_appendc(&command, ch);
            continue; 
        }

        printf("%c", ch);
    }
    while (ch != EOF);
    
    fclose(input_file);
    return 0;
}
