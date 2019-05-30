#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../library/utils.cpp"
#include "errors.hpp"
#include "../library/testutil.cpp"

// test cases
#include "iotest.cpp"
#include "lexertest.cpp"
#include "parsertest.cpp"

using std::cout;
using std::endl;


int main(const int argc, const char** argv) {
    
    // IO tests
    IO::IO io = IO::IO();
    test("IO throws error on not found file", throws_error_on_not_found_file(io));
    test("IO can read in example file", io_can_read_in_example_file(io));

    // Parser's input stream test
    test("InputStream should behave as expected", input_stream_should_behave_as_expected());

    // Lexer's token test
    test("Token should behave as expected", token_should_behave_as_expected());

    // Lexer tests
    Lexer::Lexer lexer = Lexer::Lexer();
    //test("Lexer can recognize simple expressions", lexer_can_recognize_simple(lexer));
    //test("Lexer throws an error on unproper keyword usage", lexer_throws_err_on_bad_keyword_usage(lexer));

    // Parser tests
    //Parser::Parser parser = Parser::Parser();
    //test("Parser", false);

    return 0;
}
