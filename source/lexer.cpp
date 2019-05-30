#include "lexer.hpp"


/**
 * Token
 */
Lexer::Token::Token(std::string type, std::string value) {
    this->type = type;
    this->value = value;
}


/**
 * Lexer
 */
Lexer::Lexer::Lexer() {
    this->lines = {};
}

Lexer::Lexer::Lexer(std::vector<std::string> lines) {
    this->lines = lines;
}

std::vector<std::string> Lexer::Lexer::lex(std::string line) {
    std::vector<std::string> tokens = {};
    std::string trimed_line = line;
    Utils::trim(trimed_line);

    // TODO

    return tokens;
}
