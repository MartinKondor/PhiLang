#include <iostream>
#include <string>

#include "main.hpp"
#include "input_stream.hpp"
#include "token_stream.hpp"
#include "parser.hpp"

#include "ast.hpp"


int main(const int argc, const char** argv)
{
    if (argc < 2)
    {
        show_help();
        return EXIT_SUCCESS;
    }

    // Specify input file path
    std::string inputFilePath;

    if (argv[1][0] == '/' || argv[1][0] == '\\')
    {
        inputFilePath = argv[1];
    }
    else
    {
        inputFilePath = getcwd() + '/' + argv[1];
    }

    // Check if the file is existing or not
    if (!is_file_exists(inputFilePath))
    {
        std::cout << "Can't open file '" + inputFilePath + "':" << std::endl << "No such file or directory" << std::endl;
        return EXIT_FAILURE;
    }

    InputStream is(read_file(inputFilePath));
    TokenStream ts(is);
    Parser parser(ts);

    // Show ast
    for (ASTNode node : parser.parse().nodes)
    {
        std::cout << node.value.to_str() << ",\tID: " << node.id << ",\tBase: " << node.parent_id << std::endl;
    }

    return EXIT_SUCCESS;
}

std::string getcwd()
{
    char buff[FILENAME_MAX];
    built_in_getcwd(buff, FILENAME_MAX);
    return std::string(buff);
}

bool is_file_exists(const std::string file_name)
{
    struct stat buffer;
    return (stat(file_name.c_str(), &buffer) == 0);
}

std::string read_file(const std::string file_name)
{
    FILE* input_file = fopen(file_name.c_str(), "r");
    std::string data = "";
    char* line = NULL;
    size_t len = 0;

    while (getline(&line, &len, input_file) != -1)
    {
        data += line;
    }

    fclose(input_file);
    free(line);
    return data;
}

unsigned int get_op_precedence(const std::string op_str)
{
    if (op_str == "=")
        return 1;
    if (op_str == "||")
        return 2;
    if (op_str == "&&")
        return 3;
    if (op_str == "<")
        return 7;
    if (op_str == ">")
        return 7;
    if (op_str == "<=")
        return 7;
    if (op_str == ">=")
        return 7;
    if (op_str == "==")
        return 7;
    if (op_str == "!=")
        return 7;
    if (op_str == "+")
        return 10;
    if (op_str == "-")
        return 10;
    if (op_str == "*")
        return 20;
    if (op_str == "/")
        return 20;
    if (op_str == "%")
        return 20;
    return -1;
}

void show_help()
{
    std::cout << "PhiLang BETA" << std::endl;
}
