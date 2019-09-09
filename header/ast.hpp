/*--------------------------------------------

Abstract syntax tree and it's data types.

--------------------------------------------*/
#ifndef _AST_HPP_
#define _AST_HPP_

class ASTNode {
public:
    int id;
    int parent_id;
    std::string value;

    ASTNode(const int parent_id, const std::string value);
    ASTNode(const int id, const int parent_id, const std::string value);
};


class AST {
    /**
    Example:

    ```
    AST ast;
    int parent_node_id = ast.add_node(ast.last_id, "base");
    int left_node_id = ast.add_node(parent_node_id, "left");
    int right_node_id = ast.add_node(parent_node_id, "right");

    int left_node_child_id = ast.add_node(left_node_id, "left c");

    int right_node_child_id = ast.add_node(right_node_id, "right c");
    int right_node_child_child_id = ast.add_node(right_node_id, "right cc");


    for (ASTNode node : ast.get_children(right_node_id)) {
        cout << node.value << endl;
    }
    ```
    */
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
    const int add_node(const int parent_id, const std::string value);
};

#endif // _AST_HPP_
