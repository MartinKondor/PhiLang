#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

class Token {
private:
    std::string m_type;
    std::string m_value;

public:
    Token();
    Token(const std::string &type, const std::string &value);
    std::string to_str();
    const bool is_null();
};

#endif // _TOKEN_HPP_
