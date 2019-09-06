#include "../header/input_stream.hpp"


InputStream::InputStream(const std::string &input_string="") {
    this->input_string = input_string;
    this->pos_index = 0;
    this->line_index = 1;
    this->column_index = 0;
}

const char InputStream::peek() {
    return this->pos_index < this->input_string.length() ? this->input_string[this->pos_index] : '\0';
}

const char InputStream::next() {
    const char ch = this->input_string[this->pos_index];

    if (ch == '\n') {
        this->line_index++;
        this->column_index = 0;
    }
    else {
        this->column_index++;
    }

    if (this->pos_index >= this->input_string.length()) {
        return '\0';
    }
    else {
        this->pos_index++;
    }

    return ch;
}

const bool InputStream::eof() {
    return this->peek() == '\0';
}

InputStream::~InputStream() {
    delete &this->input_string;
    delete &this->pos_index;
    delete &this->line_index;
    delete &this->column_index;
}
