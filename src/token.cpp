#include "token.hpp"


Token::Token()
{
    this->m_type = "null";
    this->m_value = "null";
}

Token::Token(const std::string &type, const std::string &value)
{
    this->m_type = type;
    this->m_value = value;
}

std::string Token::get_type()
{
    return this->m_type;
}

std::string Token::get_value()
{
    return this->m_value;
}

bool Token::is_null()
{
    return this->m_type == "null";
}

std::string Token::to_str()
{
    return "{type: " + this->m_type + ", value: " + this->m_value + "}";
}
