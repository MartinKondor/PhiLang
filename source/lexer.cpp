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
Lexer::Lexer::Lexer() {}
