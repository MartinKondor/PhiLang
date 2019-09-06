#include "../header/io.hpp"


const std::string IO::read_file(const std::string &filepath) {
    FILE* input_file = fopen(filepath.c_str(), "r");
    std::string data = "";
    char* line = NULL;
    size_t len = 0;

    while (getline(&line, &len, input_file) != -1) {
        data += line;
    }

    fclose(input_file);
    free(line);
    return data;
}

inline bool IO::is_file_exists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}
