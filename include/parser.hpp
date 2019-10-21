#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <vector>
#include "main.hpp"
#include "ast.hpp"
#include "token_stream.hpp"
#include "token.hpp"


class Parser
{
private:
    unsigned int base_node_id;
    TokenStream input;
    AST ast;

public:

    Parser(TokenStream &input);
    void unexpected();
    bool is_endl();
    bool is_punc(const std::string str);
    bool is_keyword();
    bool is_op();
    bool skip_endl();
    bool skip_punc(const std::string str);
    bool skip_keyword();
    bool skip_op();

    void parse_var();

    /**
    * @returns The Tokens between the two given start and stop strings separated with the separator
    */
    std::vector<Token> delimited(const std::string start, const std::string stop, const std::string separator);

    /**
    * Parse function call
    */
    bool maybe_call();
    bool maybe_assignment();
    AST parse();
};

#endif // _PARSER_HPP_
