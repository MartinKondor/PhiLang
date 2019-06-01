#include "parser.hpp"


/**
 * Input stream
 */
PARSER::InputStream::InputStream() {
    this->input = "";
    this->line_number = 0;
    this->line_column = 0;
    this->current_pos = 0;
}

PARSER::InputStream::InputStream(std::string input) {
    this->input = input;
    this->line_number = 0;
    this->line_column = 0;
    this->current_pos = 0;
}

char PARSER::InputStream::next() {
    char ch = this->input[this->current_pos++];
    if (ch == '\n') {
        this->line_number++;
        this->line_column = 0;
    } else {
        this->line_column++;
    }
    return ch;
}

char PARSER::InputStream::peek() {
    return this->input[this->current_pos];
}

bool PARSER::InputStream::is_eof() {
    return this->input.length() == this->current_pos;
}

void PARSER::InputStream::croak(std::string msg) {
    throw new Phi_Error(msg + " At: ("
        + Utils::to_string(this->line_number) + ":" + Utils::to_string(this->line_column) + ")");
}

/**
 * Parser
 */
PARSER::Parser::Parser() {}
