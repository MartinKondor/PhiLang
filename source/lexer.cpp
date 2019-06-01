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
LEXER::Lexer::Lexer(PARSER::InputStream input_stream) {
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

bool LEXER::Lexer::is_digit(char ch) {
    return isdigit(ch);
}

bool LEXER::Lexer::is_operator(std::string input) {
    for (std::string op : LEXER::OPERATORS) {
        if (input == op) {
            return true;
        }
    }
    return false;
}

// ,;(){}[]
bool LEXER::Lexer::is_punc(char ch) {
    return ispunct(ch);
}

bool LEXER::Lexer::is_id(std::string input) {
    std::regex var_regex("^[^\\s0-9][a-zA-Z0-9]*");
    return std::regex_match(input, var_regex);
}

bool LEXER::Lexer::is_def(std::string input) {
    std::regex func_regex("^def\\s{1,}[^0-9][a-zA-Z0-9]*\\(?([^0-9][a-zA-Z0-9]*\\,?)*\\)?");
    return std::regex_match(input, func_regex);
}
