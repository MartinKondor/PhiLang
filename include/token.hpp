#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

#include <string>


class Token
{
    /**

    num { type: "num", value: NUMBER }
    str { type: "str", value: STRING }
    bool { type: "bool", value: true or false }
    var { type: "var", value: NAME }
    endl { type: "endl", value: char }

    call { type: "call", func: AST, args: [ AST... ] }
    if { type: "if", cond: AST, then: AST, else: AST }
    OPToken : assign { type: "assign", value: "=", left: AST, right: AST }
    OPToken : binary { type: "binary", value: OPERATOR, left: AST, right: AST }
    prog { type: "prog", prog: [ AST... ] }
    */
public:
    std::string type;
    std::string value;

    Token();
    Token(const std::string &type, const std::string &value);
    bool is_null();
    std::string to_str();
};


struct BinaryToken
{
    std::string type;
    std::string op;
    Token left;
    Token right;
};

#endif // _TOKEN_HPP_
