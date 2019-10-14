#include "token.hpp"


Token::Token()
{
    this->type = "null";
    this->value = "null";
}

Token::Token(const std::string &type, const std::string &value)
{
    this->type = type;
    this->value = value;
}

bool Token::is_null()
{
    return this->type == "null";
}

std::string Token::to_str()
{
    return "{type: " + this->type + ", value: " + this->value + "}";
}
