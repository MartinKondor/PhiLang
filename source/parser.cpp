#include "parser.hpp"


/**
 * Input stream
 */
Parser::InputStream::InputStream(std::string input) {
    this->input = input;
    this->line_number = 0;
    this->line_column = 0;
    this->current_pos = 0;
}

char Parser::InputStream::next() {
    char ch = this->input[this->current_pos++];
    if (ch == '\n') {
        this->line_number++;
        this->line_column = 0;
    } else {
        this->line_column++;
    }
    return ch;
}

char Parser::InputStream::peek() {
    return this->input[this->current_pos];
}

bool Parser::InputStream::is_eof() {
    return this->input.length() == this->current_pos;
}

void Parser::InputStream::croak(std::string msg) {
    throw new Phi_Error(msg + " At: ("
        + std::to_string(this->line_number) + ":" + std::to_string(this->line_column)
        + ")");
}

/**
 * Parser
 */
Parser::Parser::Parser() {}
