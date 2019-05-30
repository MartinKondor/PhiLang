#include "io.hpp"


IO::IO::IO() {}

const std::vector<std::string> IO::IO::read_file(std::string filepath) {
    std::vector<std::string> lines = {};

    // read and store the lines of the file
    std::string line;
    std::ifstream input_file(filepath);

    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            lines.push_back(line);
        }
    }
    else {
        throw "Can't open input file.";
    }
    input_file.close();

    return lines;
}
