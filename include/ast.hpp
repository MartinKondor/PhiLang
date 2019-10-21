#ifndef _AST_HPP_
#define _AST_HPP_

#include <vector>
#include "token.hpp"


class ASTNode
{
public:
    unsigned int id;
    unsigned int parent_id;
    Token value;

    ASTNode(const unsigned int parent_id, Token value);
    ASTNode(const unsigned int id, const unsigned int parent_id, Token value);
};


class AST
{
public:
    unsigned int last_id;
    std::vector<ASTNode> nodes;


    AST();

    /**
    * @returns the children nodes of the given parent.
    */
    std::vector<ASTNode> get_children(const unsigned int parent_id);

    /**
    * @returns the created node's id
    */
    unsigned int add_node(const unsigned int parent_id, Token value);
};

#endif // _AST_HPP_
