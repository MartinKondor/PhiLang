#include "phi.h"


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

    String code = String_init("");
    char ch;

    do 
    {
        ch = fgetc(input_file);
        String_appendc(&code, ch);
    }
    while (ch != EOF);
    fclose(input_file);

    // For debuging
    PhiStack stack = Phi_eval(code, 0);

    printf("Variables:\n");
    for (unsigned int i = 0; i < stack.variables.length; i++) 
    {
        PhiVariable_print(*PhiVariableList_at(stack.variables, i));
    }

    printf("\nFunctions:\n");
    for (unsigned int i = 0; i < stack.functions.length; i++) 
    {
        PhiFunction_print(*PhiFunctionList_at(stack.functions, i));
    }

    free(stack.variables.storage);
    free(stack.functions.storage);
    return 0;
}
