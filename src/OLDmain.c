#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "types.h"


int OLDmain(const int argc, const char** argv)
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

    unsigned int code_mem_size = 1024 * 1024, code_index = 0;
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

    Phi_eval(code);
    free(code);
    return 0;
}

void Phi_execToken(char* token)
{
    for (unsigned int i = 0; i < sizeof(token) / sizeof(*token); i++)
    {
        
    }
}

void Phi_eval(char* code)
{
    bool in_one_line_comment = false;
    unsigned int token_mem_size = 1024, token_index = 0,
                ch_index = 0, line_index = 0;
    char* token = (char*) malloc(token_mem_size);

    // Go char by char
    for (; ch_index < strlen(code); ch_index++)
    {
        // if (code[ch_index] == ' ' || code[ch_index] == '\n' || code[ch_index] == '\r') continue;  // Ignore whitespace
        if (code[ch_index] == '#')
        {
            in_one_line_comment = true;
            continue;
        }

        if (code[ch_index] == '\n' || code[ch_index] == '\r')
        {
            in_one_line_comment = false;
            line_index++;
            continue;
        }

        if (in_one_line_comment) continue;

        // Reserve more memory for the token
        if (token_index >= token_mem_size)
        {
            token_mem_size *= 2;
            token = realloc(token, token_mem_size);
        }

        // Execute token
        if (code[ch_index] == '!')
        {
            token[token_index] = '\0';
            Phi_execToken(token);
            free(token);
            token_mem_size = 1024;
            token = (char*) malloc(token_mem_size);
            token_index = 0;
            continue;
        }

        token[token_index++] = code[ch_index];
    }
    free(token);
}
