#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iterator>
#include <regex>

#include "../library/utils.cpp"
#include "errors.hpp"
#include "../library/testutil.cpp"

// test cases
#include "iotest.cpp"
#include "parsertest.cpp"
#include "lexertest.cpp"

using std::cout;
using std::endl;


int main(const int argc, const char** argv) {
    cout << "##################################" << endl;

    // IO tests
    IO::IO io = IO::IO();
    test("IO throws error on not found file", throws_error_on_not_found_file(io));
    test("IO can read in example file as vector", io_can_read_in_example_file(io));
    test("IO can read in example file as string", io_can_read_in_example_file_as_str(io));

    // Parser's input stream test
    test("Parser woks on one line", input_stream_woks_on_one_line());
    test("Parser woks on multipe lines", input_stream_woks_on_multipe_lines());

    // Lexer's token test
    test("Token should behave as expected", token_should_behave_as_expected());

    // Lexer tests
    test("Lexer can recognize simple expressions", lexer_can_recognize_simple());
    test("Lexer can recognize variables", lexer_can_recognize_var());
    test("Lexer can recognize function definitions", lexer_can_recognize_func());

    // Parser tests
    PARSER::Parser parser = PARSER::Parser();
    test("Parser", false);

    return 0;
}
