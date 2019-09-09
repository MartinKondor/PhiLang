#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <regex>
#include <sys/stat.h>
#include <unordered_map>

using std::cout;
using std::endl;

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#define built_in_getcwd _getcwd
#define OS_NAME "Windows"
#else
#include <unistd.h>
#define built_in_getcwd getcwd
#define OS_NAME "Linux"
#endif // _WIN32

#define PHI_VERSION "v0.0.1"

#include "errors.cpp"
#include "utils.cpp"

// Global variables
const std::string CURRENT_WORKING_DIR = Utils::getcwd();
const std::string NOT_ID_STRING = "?!-<>=0123456789";
const std::string KEYWORDS = " if else while for def true false ";
const std::regex DIGIT_REGEX("[0-9]");
const std::regex ID_START_REGEX("[a-z_]");
const std::regex OPERATOR_REGEX("[\\+\\-%=&\\|<>!/\\*]");
const std::regex PUNC_REGEX("[\\(\\)\[\\]\{\\},;]");

#include "io.cpp"
#include "input_stream.cpp"
#include "token.cpp"
#include "token_stream.cpp"
#include "ast.cpp"
#include "parser.cpp"


int main(const int argc, const char** argv) {
    if (argc < 2) {
        CommandUtils::show_help();
        system("pause");
        return EXIT_SUCCESS;
    }

    // Specify input file path
    std::string inputFilePath;

    if (argv[1][0] == '/' || argv[1][0] == '\\') {
        inputFilePath = argv[1];
    }
    else {
        inputFilePath = CURRENT_WORKING_DIR + '/' + argv[1];
    }

    // Check if the file is existing or not
    if (!IO::is_file_exists(inputFilePath)) {
        cout << "Can't open file '" + inputFilePath + "': No such file or directory" << endl;
        exit(EXIT_FAILURE);
    }

    InputStream is(IO::read_file(inputFilePath));
    TokenStream ts(is);
    Parser parser(ts);

    return EXIT_SUCCESS;
}
