#include "parser.hpp"

#include <iostream>  // Temporarily


Parser::Parser(TokenStream &input)
{
    this->input = input;
}

void Parser::unexpected()
{
    this->input.croak("Unexpected token: " + this->input.next().get_value());
}

void Parser::start()
{
    std::cout << this->input.next().to_str() << std::endl;
}
