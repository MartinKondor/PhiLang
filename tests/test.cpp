#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "../src/ast.cpp"
#include "../src/utils.cpp"
#include "../src/lexer.cpp"
#include "tlexer.cpp"

int main(const int argc, const char** args) {
    testLexing();    
    std::cout << "Testing is finished." << std::endl;
    return 0;
}
