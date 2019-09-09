#include "../header/token_stream.hpp"


TokenStream::TokenStream() {}

TokenStream::TokenStream(const InputStream &input) {
    this->input = input;
    this->stopped = false;
}

const bool TokenStream::is_digit(const char &ch) {
    return std::regex_match(Utils::to_string(ch), DIGIT_REGEX);
}

const bool TokenStream::is_keyword(const std::string &str) {
    return KEYWORDS.find(" " + str + " ") != std::string::npos;
}

const bool TokenStream::is_id_start(const char &ch) {
    return std::regex_match(Utils::to_string(ch), ID_START_REGEX);
}

const bool TokenStream::is_id(const char &ch) {
    return this->is_id_start(ch) || NOT_ID_STRING.find(ch) != std::string::npos;
}

const bool TokenStream::is_op_char(const char &ch) {
    return std::regex_match(Utils::to_string(ch), OPERATOR_REGEX);
}

const bool TokenStream::is_punc(const char &ch) {
    return std::regex_match(Utils::to_string(ch), PUNC_REGEX);
}

const bool TokenStream::is_whitespace(const char &ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

const bool TokenStream::is_new_line(const char &ch) {
    return ch == '\n';
}

const bool TokenStream::is_not_new_line(const char &ch) {
    return !this->is_new_line(ch);
}

const std::string TokenStream::read_while(const bool (TokenStream::*func)(const char&)) {
    std::string str;

    while (!this->input.eof() && (this->*func)(this->input.peek())) {
        str += this->input.next();
    }

    return str;
}

const std::string TokenStream::read_escaped(const char &end) {
    bool escaped = false;
    std::string str = "";
    char ch;
    this->input.next();

    while (!this->input.eof()) {
        ch = this->input.next();

        if (escaped) {
            str += ch;
            escaped = false;
        }
        else if (ch == '\\') {
            escaped = true;
        }
        else if (ch == end) {
            break;
        }
        else {
            str += ch;
        }
    }
    return str;
}

Token TokenStream::read_string() {
    return Token("str", read_escaped('"'));
}

const void TokenStream::skip_comment() {
    read_while(this->is_not_new_line);
    this->input.next();
}

Token TokenStream::peek() {
    if (this->currentToken.is_null()) {
        this->currentToken = this->read_next();
    }
    return this->currentToken;
}

const bool TokenStream::eof() {
    this->peek();
    return this->currentToken.is_null();
}

Token TokenStream::read_next() {
    this->read_while(is_whitespace);

    if (this->input.eof()) {
        return Token("null", "null");
    }

    char ch = this->input.peek();

    if (ch == '#') {
        this->skip_comment();
        return this->read_next();
    }
    if (ch == '"') {
        return this->read_string();
    }
    if (this->is_digit(ch)) {
        return this->read_number();
    }
    if (this->is_id_start(ch)) {
        return this->read_ident();
    }
    if (this->is_punc(ch)) {
        return Token("punc", Utils::to_string(this->input.next()));
    }
    if (this->is_op_char(ch)) {
        return Token("op", this->read_while(this->is_op_char));
    }

    this->croak("Can't handle character: " + ch);
}

const bool TokenStream::has_dot(const char &ch) {
    // ???
    bool has_dot = false;
    if (ch == '.') {
        if (has_dot) {
            return false;
        }
        has_dot = true;
        return true;
    }
    return this->is_digit(ch);
}

Token TokenStream::read_number() {
    return Token("num", read_while(this->has_dot));
}

Token TokenStream::next() {
    if (!this->stopped) {
        Token tok = this->currentToken;
        this->currentToken = Token("null", "null");

        if (tok.is_null()) {
            tok = read_next();

            if (tok.is_null()) {
                this->stopped = true;
            }
        }
        return tok;
    }
    return Token("null", "null");
}

Token TokenStream::read_ident() {
    std::string id = read_while(is_id);
    return Token(this->is_keyword(id) ? "kw" : "var", id);
}

const void TokenStream::croak(const std::string &msg) {
    this->input.croak(msg);
}
