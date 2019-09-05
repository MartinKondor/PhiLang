#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <sys/stat.h>

using std::cout;
using std::endl;

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#define __getcwd _getcwd
#define OS_NAME "Windows"
#else
#include <unistd.h>
#define __getcwd getcwd
#define OS_NAME "Linux"
#endif // _WIN32

#define PHI_VERSION "v0.0.1"

#include "errors.cpp"
#include "utils.cpp"
#include "io.cpp"


// Global variables
const std::string CURRENT_WORKING_DIR = Utils::getcwd();

/// FOR TESTING

/// / FOR TESTING

int main(const int argc, const char** argv) {
    if (argc < 2) {
        CommandUtils::showHelp();
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
    IO::IO io;

    if (IO::is_file_exists(inputFilePath)) {
        cout << io.read_file_as_str(inputFilePath) << endl;
    }
    else {
        cout << "Can't open file '" + inputFilePath + "': No such file or directory" << endl;
        exit(EXIT_FAILURE);
    }



    // read from file
    // lex each line
    // parse tokens
    // evaluate
    return EXIT_SUCCESS;
}
