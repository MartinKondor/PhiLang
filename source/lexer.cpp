#include "lexer.hpp"


/**
 * Token
 */
LEXER::Token::Token() {
    this->type = "null";
    this->value = "null";
}

LEXER::Token::Token(std::string type, std::string value) {
    this->type = type;
    this->value = value;
}


/**
* Lexer
*/
LEXER::Lexer::Lexer(PARSER::InputStream* input_stream) {
    this->input_stream = input_stream;
    this->current_token = LEXER::Token();
}

/**
* static methods
*/
bool LEXER::Lexer::is_whitespace(char ch) {
    return isspace(ch);
}

bool LEXER::Lexer::is_keyword(std::string input) {
    for (std::string keyword : LEXER::KEYWORDS) {
        if (input == keyword) {
            return true;
        }
    }
    return false;
}
