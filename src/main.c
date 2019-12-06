#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(const int argc, const char** argv)
{
    if (argc < 2)
    {
        printf("Process terminated.\nNo input file provided.\n");
        return 0;
    }

    FILE* input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Input file cannot be opened.\n");
        return 1;
    }

    unsigned int code_mem_size = 1024;
    unsigned int code_index = 0;
    char* code = (char*) malloc(code_mem_size);
    char ch;

    do
    {
        ch = fgetc(input_file);

        // Realloc more memory
        if (code_index >= code_mem_size)
        {
            code_mem_size *= 2;
            code = realloc(code, code_mem_size);
        }

        code[code_index++] = ch;
    }
    while (ch != EOF);

    fclose(input_file);
    code[code_index] = '\0';

    // Free up some memory
    code = memmove(code, code - (strlen(code) - code_index), strlen(code));
    
    // code

    free(code);
    return 0;
}
