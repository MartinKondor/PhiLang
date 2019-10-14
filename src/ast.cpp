#include "ast.hpp"


ASTNode::ASTNode(const int parent_id, Token value)
{
    this->id = -1;
    this->parent_id = parent_id;
    this->value = value;
}

ASTNode::ASTNode(const int id, const int parent_id, Token value)
{
    this->id = id;
    this->parent_id = parent_id;
    this->value = value;
}


AST::AST()
{
    this->last_id = 0;
}

std::vector<ASTNode> AST::get_children(const int parent_id)
{
    std::vector<ASTNode> children;
    for (ASTNode node : this->nodes)
    {
        if (node.parent_id == parent_id)
        {
            children.push_back(node);
        }
    }
    return children;
}

int AST::add_node(const int parent_id, Token value)
{
    this->nodes.push_back(ASTNode(++this->last_id, parent_id, value));
    return this->last_id;
}
