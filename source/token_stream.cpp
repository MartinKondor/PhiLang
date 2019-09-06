#include "../header/token_stream.hpp"


class TokenStream {
private:
    InputStream input;
    Token currentToken;
    std::string currentTokenString;

public:

    TokenStream(const InputStream &input) {
        this->input = input;
        this->currentTokenString = "";
    }

    const bool is_digit(const char &ch) {
        return std::regex_match(Utils::to_string(ch), DIGIT_REGEX);
    }

    const bool is_keyword(const std::string &str) {
        return KEYWORDS.find(" " + str + " ") != std::string::npos;
    }

    const bool is_id_start(const char &ch) {
        return std::regex_match(Utils::to_string(ch), ID_START_REGEX);
    }

    const bool is_id(const char &ch) {
        return this->is_id_start(ch) || NOT_ID_STRING.find(ch) != std::string::npos;
    }

    const bool is_op_char(const char &ch) {
        return std::regex_match(Utils::to_string(ch), OPERATOR_REGEX);
    }

    const bool is_punc(const char &ch) {
        return std::regex_match(Utils::to_string(ch), PUNC_REGEX);
    }

    const bool is_whitespace(const char &ch) {
        return ch == ' ' || ch == '\t' || ch == '\n';
    }

    /**
    Reads from input stream until the given function returns false
    @returns string of the read content
    */
    const std::string read_while(const bool (TokenStream::*func)(const char&)) {
        std::string str;

        while (!this->input.eof() && (this->*func)(this->input.peek())) {
            str += this->input.next();
        }

        return str;
    }

    const bool is_new_line(const char &ch) {
        return ch == '\n';
    }

    const bool is_not_new_line(const char &ch) {
        return !this->is_new_line(ch);
    }

    /**
    Reads until the end parameter is found
    @returns string of the read content
    */
    const std::string read_escaped(const char &end) {
        bool escaped = false;
        std::string str = "";
        this->input.next();

        while (!this->input.eof()) {
            char ch = this->input.next();

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

    Token read_string() {
        return Token("str", read_escaped('"'));
    }

    /**
    Skips input stream content until newline
    */
    const void skip_comment() {
        read_while(this->is_not_new_line);
        this->input.next();
    }

    Token peek() {
        // return this->currentTokenString || (this->currentTokenString = Utils::to_string(read_next()));
        if (this->currentToken.is_null()) {
            this->currentToken = this->read_next();
        }
        return this->currentToken;
    }

    const bool eof() {
        this->peek();
        return this->currentToken.is_null();
    }

    Token read_next() {
        read_while(is_whitespace);

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

        if (is_op_char(ch)) {
            return Token("op", this->read_while(this->is_op_char));
        }

        this->input.croak("Can't handle character: " + ch);
    }

    const bool has_dot(const char &ch) {
        /// TODO: ???
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

    Token read_number() {
        return Token("num", read_while(this->has_dot));
    }

    Token next() {
        Token tok = this->currentToken;
        this->currentToken = Token("null", "null");

        if (tok.is_null()) {
            tok = read_next();
        }
        return tok;
    }

    Token read_ident() {
        std::string id = read_while(is_id);
        return Token(this->is_keyword(id) ? "kw" : "var", id);
    }

};
