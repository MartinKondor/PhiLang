#include "parser.hpp"

#include <iostream>  // Temporarily


Parser::Parser(TokenStream &input)
{
    this->input = input;
    this->base_node_id = 0;
    this->ast = AST();
}

void Parser::unexpected()
{
    this->input.croak("Unexpected token: " + this->input.next().value);
}

bool Parser::is_endl()
{
    // || this->input.peek().type == "null"
    return this->input.peek().type == "endl";
}

bool Parser::is_punc(const std::string str)
{
    return this->input.peek().value == str && this->input.peek().type == "punc";
}

bool Parser::is_keyword()
{
    return this->input.peek().type == "kw";
}

bool Parser::is_op()
{
    return this->input.peek().type == "op";
}

bool Parser::skip_endl()
{
    if (this->is_endl())
        this->input.next();
    else
        this->input.croak("Expecting end of line character: \"" + this->input.peek().value + "\"");
}

bool Parser::skip_punc(const std::string str)
{
    if (this->is_punc(str))
        this->input.next();
    else
        this->input.croak("Expecting punctuation \"" + str + "\": \"" + this->input.peek().value + "\"");
}

bool Parser::skip_keyword()
{
    if (this->is_keyword())
        this->input.next();
    else
        this->input.croak("Expecting keyword: \"" + this->input.peek().value + "\"");
}

bool Parser::skip_op()
{
    if (this->is_op())
        this->input.next();
    else
        this->input.croak("Expecting operator: \"" + this->input.peek().value + "\"");
}

std::vector<Token> Parser::delimited(const std::string start, const std::string stop, const std::string separator)
{
    std::vector<Token> container;
    bool first = true;

    this->skip_punc(start);

    while (!this->input.eof())
    {
        if (this->is_punc(stop))
            break;

        if (first)
            first = false;
        else
            skip_punc(separator);

        if (this->is_punc(stop))
            break;
        container.push_back(this->input.next());
    }
    skip_punc(stop);
    return container;
}

bool Parser::maybe_call()
{
    if (this->input.peek().value != "(")
    {
        return false;
    }

    for (Token param : this->delimited("(", ")", ","))
    {
        this->ast.add_node(this->base_node_id, param);
    }
    return true;
}

bool Parser::maybe_assignment()
{
    Token op_tok = this->input.peek();
    if (op_tok.type != "op")
    {
        return false;
    }

    // Set op to be the base node
    // int op_node_id = this->ast.add_node(this->base_node_id, op_tok);
    // int prev_base_node_id = this->base_node_id;
    // this->base_node_id = op_node_id;
    this->input.next(); // Throw the operator

    // Parse in the value
    Token tok;

    while (this->input.peek().type != "endl")
    {
        tok = this->input.next();
        if (tok.type == "op") tok.precedence = get_op_precedence(tok.value);
        this->ast.add_node(this->base_node_id, tok);
    }

    // this->base_node_id = prev_base_node_id;
    return true;
}

bool Parser::parse_atom()
{
    Token var_tok = this->input.peek();

    if (var_tok.type == "var")
    {
        // Set var to the base node
        int var_node_id = this->ast.add_node(this->base_node_id, var_tok);
        int prev_base_node_id = this->base_node_id;
        this->base_node_id = var_node_id;
        this->input.next();  // Throw the var token

        if (is_punc("(")) return this->maybe_call();
        if (is_op()) return this->maybe_assignment();

        this->base_node_id = prev_base_node_id;
    }
}

AST Parser::parse()
{
    while (!this->input.eof())
    {
        this->parse_atom();
        this->skip_endl();
    }
    return this->ast;
}
