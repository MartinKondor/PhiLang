#include "../header/input_stream.hpp"


InputStream::InputStream(const std::string &input) {
    this->input = input;

    /* Testing
    while (!this->eof()) {
        cout << this->next();
    }
    */
}

const char InputStream::peek() {
    return this->input[this->pos];
}

const char InputStream::next() {
    const char ch = this->input[this->pos++];
    if (ch == '\n') {
        this->line++;
        this->col = 0;
    }
    else {
        this->col++;
    }
    return ch;
}

const bool InputStream::eof() {
    return this->peek() == '\0';
}

Phi_Error* InputStream::croak(const std::string &msg) {
    throw new Phi_Error(msg);
}

InputStream::~InputStream() {}
