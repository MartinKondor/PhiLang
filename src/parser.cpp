#include "parser.hpp"

#include <iostream>  // Temporarily


Parser::Parser(TokenStream &input)
{
    this->input = input;
    this->base_node_id = 0;
    this->ast = AST();
}

bool Parser::is_punc(const char &ch)
{
    Token tok = this->input.peek();
    return !tok.is_null() && tok.get_type() == "punc" && tok.get_value() == to_string(ch);
}

bool Parser::is_keyword(const char &kw)
{
    Token tok = this->input.peek();
    return !tok.is_null() && tok.get_type() == "kw" && tok.get_value() == to_string(kw);
}

bool Parser::is_op(const char &op)
{
    Token tok = this->input.peek();
    return !tok.is_null() && tok.get_type() == "op" && tok.get_value() == to_string(op);
}

bool Parser::skip_punc(const char &ch)
{
    if (this->is_punc(ch))
    {
        this->input.next();
    }
    else
    {
        this->input.croak("Expecting punctuation: \"" + to_string(ch) + "\"");
    }
}

bool Parser::skip_keyword(const char &kw)
{
    if (this->is_keyword(kw))
    {
        this->input.next();
    }
    else
    {
        this->input.croak("Expecting keyword: \"" + to_string(kw) + "\"");
    }
}

bool Parser::skip_op(const char &op)
{
    if (this->is_op(op))
    {
        this->input.next();
    }
    else
    {
        this->input.croak("Expecting operator: \"" + to_string(op) + "\"");
    }
}

void Parser::maybe_assignment(int var_node_id)
{
    Token op_tok = this->input.next();
    int op_node_id = this->ast.add_node(var_node_id, op_tok);  // Create a node for the operator
    Token right = this->input.next();

    if (right.get_type() == "num" || right.get_type() == "str" ||
        right.get_type() == "var")
    {
        this->ast.add_node(op_node_id, right);  // Create a node for the right side
    }
    else
    {
        this->unexpected();
    }
}

void Parser::maybe_function_call(int var_node_id)
{
    this->unexpected();
}

void Parser::parse_var()
{
    int var_node_id = this->ast.add_node(this->base_node_id, this->input.next());

    if (this->input.peek().get_type() == "op")
    {
        this->maybe_assignment(var_node_id);
    }
    else if (this->input.peek().get_value() == "(")
    {
        this->maybe_function_call(var_node_id);
    }
    else
    {
        this->unexpected();
    }
}

void Parser::unexpected()
{
    this->input.croak("Unexpected token: " + this->input.next().get_value());
}

AST Parser::start()
{
    while (!this->input.eof())
    {
        std::cout << this->input.peek().to_str() << std::endl;

        if (this->input.peek().get_type() == "var")
        {
            this->parse_var();
        }
        else
        {
            this->unexpected();
        }
    }
    return this->ast;
}
