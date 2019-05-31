#include "../source/io.cpp"


const bool throws_error_on_not_found_file(IO::IO& io) {
    try {
        io.read_file("tests/data/nonexistingfile.xyz");
    }
    catch (Phi_Error err) {
        try {
            io.read_file_as_str("tests/data/nonexistingfile.xyz");
        }
        catch (Phi_Error err) {
            return true;
        }
    }
    return false;
}

const bool io_can_read_in_example_file(IO::IO& io) {
    std::vector<std::string> lines =  io.read_file("tests/testdata/io.txt");
    return lines.size() == 1 && lines[0] == "R";
}

const bool io_can_read_in_example_file_as_str(IO::IO& io) {
    std::string c = io.read_file_as_str("tests/testdata/io2.txt");
    return c == "R1\nR2\n";
}
