#include "../header/token.hpp"


Token::Token() {
    this->m_type = "null";
    this->m_value = "null";
}

Token::Token(const std::string &type, const std::string &value) {
    this->m_type = type;
    this->m_value = value;
}

std::string Token::to_str() {
    return "{type: " + this->m_type + ", value: " + this->m_value + "}";
}

const bool Token::is_null() {
    return this->m_type == "null" && this->m_value == "null";
}
