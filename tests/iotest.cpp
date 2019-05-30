#include "../source/io.cpp"


bool throws_error_on_not_found_file(IO::IO& io) {
    try {
        io.read_file("tests/data/nonexistingfile.xyz");
        return false;
    }
    catch (const char* err) {
        return true;
    }
    return false;
}

bool io_can_read_in_example_file(IO::IO& io) {
    std::vector<std::string> lines =  io.read_file("tests/data/io.txt");
    return lines.size() == 1 && lines[0] == "R";
}
