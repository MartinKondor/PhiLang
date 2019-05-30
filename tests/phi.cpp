#include <iostream>
#include <vector>
#include <string>
#include "testutil.cpp"
#include "iotest.cpp"

using std::cout;
using std::endl;


int main(const int argc, const char** argv) {
    IO::IO io = IO::IO();

    test("IO throws error on not found file", throws_error_on_not_found_file(io));
    test("IO can read in example file", io_can_read_in_example_file(io));

    return 0;
}
