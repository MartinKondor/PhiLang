/*--------------------------------------------

Parser for parsing AST with TokenStream.

--------------------------------------------*/
#ifndef _PARSER_HPP_
#define _PARSER_HPP_

class Parser {
private:
    TokenStream input;
    int base_node_id;
    AST ast;

public:

    Parser(TokenStream &input) {
        this->input = input;
        this->base_node_id = 0;
        this->ast = AST();
    }

    const void parse_var() {
        int var_node_id = this->ast.add_node(this->base_node_id, this->input.next());

        if (this->input.peek().get_type() == "op") {
            int op_node_id = this->ast.add_node(var_node_id, this->input.next());
            Token right = this->input.next();

            if (right.get_type() == "var" || right.get_type() == "num" ||
                    right.get_type() == "str" || right.get_type() == "bool") {
                this->ast.add_node(op_node_id, right);
            }
            else {
                this->unexpected();
            }
        }
        else if (this->input.peek().get_value() == "(") {
            // ...
        }
        else {
            this->unexpected();
        }
    }

    AST start() {
        while (!this->input.eof()) {
            if (this->input.peek().get_type() == "var") {
                this->parse_var();
            }
            else {
                this->unexpected();
            }
        }

        return this->ast;
    }

    const void unexpected() {
        this->input.croak("Unexpected token: " + this->input.next().get_value());
    }

};

#endif // _PARSER_HPP_
