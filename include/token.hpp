#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

#include <string>


class Token
{
private:
    /**

    num { type: "num", value: NUMBER }
    str { type: "str", value: STRING }
    bool { type: "bool", value: true or false }
    var { type: "var", value: NAME }

    call { type: "call", func: AST, args: [ AST... ] }
    if { type: "if", cond: AST, then: AST, else: AST }
    assign { type: "assign", operator: "=", left: AST, right: AST }
    binary { type: "binary", operator: OPERATOR, left: AST, right: AST }
    prog { type: "prog", prog: [ AST... ] }
    */
    std::string m_type;
    std::string m_value;

public:
    Token();
    Token(const std::string &type, const std::string &value);
    const std::string get_type();
    const std::string get_value();
    const bool is_null();
    std::string to_str();
};

#endif // _TOKEN_HPP_
