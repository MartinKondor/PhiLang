#include "lexer.hpp"


/**
 * Token
 */
LEXER::Token::Token() {
    this->type = "null";
    this->value = "null";
}

LEXER::Token::Token(const std::string &type, const std::string &value) {
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
* Static methods
*/
const bool LEXER::Lexer::is_whitespace(const char &ch) {
    return isspace(ch);
}

const bool LEXER::Lexer::is_keyword(const std::string &input) {
    for (std::string keyword : LEXER::KEYWORDS) {
        if (input == keyword) {
            return true;
        }
    }
    return false;
}

const bool LEXER::Lexer::is_digit(const char &ch) {
    return isdigit(ch);
}

const bool LEXER::Lexer::is_operator(const std::string &input) {
    for (std::string op : LEXER::OPERATORS) {
        if (input == op) {
            return true;
        }
    }
    return false;
}

// ,;(){}[]
const bool LEXER::Lexer::is_punc(char &ch) {
    return ispunct(ch);
}

const bool LEXER::Lexer::is_id(const std::string &input) {
    std::regex var_regex("^[^\\s0-9][a-zA-Z0-9]*");
    return std::regex_match(input, var_regex);
}

const bool LEXER::Lexer::is_def(const std::string &input) {
    std::regex func_regex("^def\\s{1,}[^0-9][a-zA-Z0-9]*\\(?([^0-9][a-zA-Z0-9]*\\,?)*\\)?");
    return std::regex_match(input, func_regex);
}
