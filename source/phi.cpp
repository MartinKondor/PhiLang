#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../library/utils.cpp"
#include "errors.hpp"
#include "io.cpp"

using std::cout;
using std::endl;


int main(const int argc, const char** argv) {

    // handle arguments
    if (argc < 2) {
        cout << "No input file provided." << endl;
        cout << "Terminating." << endl;
        return 1;
    }

    // read from file
    IO::IO* io = new IO::IO;
    std::vector<std::string> file_lines = io->read_file(argv[1]);
    delete io;

    // lex each line
    // parse tokens
    // evaluate
    return 0;
}
