#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include "main.hpp"
#include "ast.hpp"
#include "token_stream.hpp"
#include "token.hpp"


class Parser
{
private:
    int base_node_id;
    TokenStream input;
    AST ast;

public:

    Parser(TokenStream &input);

    bool is_punc(const char &ch);
    bool is_keyword(const char &kw);
    bool is_op(const char &op);
    bool skip_punc(const char &ch);
    bool skip_keyword(const char &kw);
    bool skip_op(const char &op);

    void maybe_function_call(int var_node_id);
    void maybe_assignment(int var_node_id);
    void parse_var();

    /**
    * Prints out error/exception text
    */
    void unexpected();

    /**
    * Starts the parsing process
    */
    AST start();
};

#endif // _PARSER_HPP_
