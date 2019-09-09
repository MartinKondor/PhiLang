#include "../header/parser.hpp"


class Parser {
private:
    TokenStream input;

public:

    Parser(TokenStream &input) {
        this->input = input;
    }

    const bool is_punc(const char &ch) {
        Token tok = this->input.peek();
        return !tok.is_null() && tok.get_type() == "punc" && (!this->input.is_whitespace(ch) || tok.get_value() == Utils::to_string(ch));
    }

    const bool is_kw(const char &ch) {
        Token tok = this->input.peek();
        return !tok.is_null() && tok.get_type() == "kw" && (!this->input.is_whitespace(ch) || tok.get_value() == Utils::to_string(ch));
    }

    const bool is_op(const char &ch) {
        Token tok = this->input.peek();
        return !tok.is_null() && tok.get_type() == "op" && (!this->input.is_whitespace(ch) || tok.get_value() == Utils::to_string(ch));
    }

    const void unexpected() {
        this->input.croak("Unexpected token: " + this->input.peek().to_str());
    }

    const void skip_punc(const char &ch) {
        if (this->is_punc(ch)) this->input.next();
        else this->input.croak("Unexpected token: " + this->input.peek().to_str());
    }

    const void skip_kw(const char &ch) {
        if (this->is_kw(ch)) this->input.next();
        else this->input.croak("Expecting keyword: \"" + Utils::to_string(ch) + "\"");
    }

    const void skip_op(const char &ch) {
        if (this->is_op(ch)) this->input.next();
        else this->input.croak("Expecting operator: \"" + Utils::to_string(ch) + "\"");
    }

};
