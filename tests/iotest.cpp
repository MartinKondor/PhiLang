#include "../source/io.cpp"


const bool throws_error_on_not_found_file(IO::IO& io) {
    try {
        io.read_file("tests/data/nonexistingfile.xyz");
        return false;
    }
    catch (Phi_Error err) {
        return true;
    }
    return false;
}

const bool io_can_read_in_example_file(IO::IO& io) {
    std::vector<std::string> lines =  io.read_file("tests/testdata/io.txt");
    return lines.size() == 1 && lines[0] == "R";
}
