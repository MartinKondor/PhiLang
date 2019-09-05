#include "../header/io.hpp"


IO::IO::IO() {}

const std::vector<std::string> IO::IO::read_file(const std::string &filepath) {
    std::string line;
    std::vector<std::string> lines;
    std::ifstream input_file(filepath);

    // Read and store the lines of the file
    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            lines.push_back(line);
        }
    }
    else {
        throw Phi_Error("Can't open file '" + filepath + "': No such file or directory");
    }
    input_file.close();
    return lines;
}

const std::string IO::IO::read_file_as_str(const std::string &filepath) {
    std::string line;
    std::stringstream ss;
    std::ifstream input_file(filepath);

    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            ss << (line + '\n');
        }
    }
    else {
        throw Phi_Error("Can't open file '" + filepath + "': No such file or directory");
    }
    input_file.close();
    return ss.str();
}

IO::IO::~IO() {}
