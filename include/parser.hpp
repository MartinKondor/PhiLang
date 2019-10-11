#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include "token_stream.hpp"


class Parser
{
private:
    TokenStream input;

public:

    Parser(TokenStream &input);

    /**
    * Prints out error/exception text
    */
    void unexpected();

    /**
    * Starts the parsing process
    */
    void start();
};

#endif // _PARSER_HPP_
