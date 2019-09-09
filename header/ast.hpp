/*--------------------------------------------

Abstract syntax tree and it's data types.

--------------------------------------------*/
#ifndef _AST_HPP_
#define _AST_HPP_

class ASTNode {
public:
    int id;
    int parent_id;
    Token value;

    ASTNode(const int parent_id, Token value);
    ASTNode(const int id, const int parent_id, Token value);
};


class AST {
public:
    int last_id;
    std::vector<ASTNode> nodes;


    AST();

    /**
    * @returns the children nodes of the given parent.
    */
    const std::vector<ASTNode> get_children(const int parent_id);

    /**
    * @returns the created node's id
    */
    const int add_node(const int parent_id, const Token value);
};

#endif // _AST_HPP_
