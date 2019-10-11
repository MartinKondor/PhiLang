#ifndef _TOKEN_STREAM_HPP_
#define _TOKEN_STREAM_HPP_

#include <string>
#include <regex>
#include "main.hpp"
#include "token.hpp"
#include "input_stream.hpp"


class TokenStream
{
private:
    InputStream input;
    Token currentToken;
    bool stopped;

public:
    static const std::string NOT_ID_STRING;
    static const std::string KEYWORDS;
    static const std::regex DIGIT_REGEX;
    static const std::regex ID_START_REGEX;
    static const std::regex OPERATOR_REGEX;
    static const std::regex PUNC_REGEX;


    TokenStream();
    TokenStream(const InputStream &input);
    const bool is_digit(const char &ch);
    const bool is_keyword(const std::string &str);
    const bool is_id_start(const char &ch);
    const bool is_id(const char &ch);
    const bool is_op_char(const char &ch);
    const bool is_punc(const char &ch);
    const bool is_whitespace(const char &ch);
    const bool is_new_line(const char &ch);
    const bool is_not_new_line(const char &ch);
    Token read_string();
    Token peek();
    const bool eof();
    Token read_next();
    const bool has_dot(const char &ch);
    Token read_number();
    Token next();
    Token read_ident();

    /**
    Reads from input stream until the given function returns false
    @returns string of the read content
    */
    const std::string read_while(const bool (TokenStream::*func)(const char&));

    /**
    Reads until the given end parameter is found
    @returns string of the read content
    */
    const std::string read_escaped(const char &end);

    /**
    Skips input stream content until newline
    */
    const void skip_comment();

    /**
    * Throws a Phi_Error
    */
    const void croak(const std::string &msg);
};

#endif // _TOKEN_STREAM_HPP_
