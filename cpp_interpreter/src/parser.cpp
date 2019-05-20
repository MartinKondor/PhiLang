#include <iostream>

const uint8_t N_OF_OPERATORS = 14;
const std::string OPERATORS[N_OF_OPERATORS] = {
    "==", "!=", "+=", "-=", ">=", "<=",
    "=", ">", "<", "/", "*", "%", "+", "-",
};

const uint8_t N_OF_KEYWORDS = 27;
const std::string KEYWORDS[N_OF_KEYWORDS] = {
    "if", "else", "elseif", "while", "for", "in",
	"continue", "break", "true", "false", "null",
	"and", "or", "not", "def", "return", "const",
	"try", "catch", "throw", "as", "import", "delete",
    "finally", "is", "pass", "yield"
};

namespace Parser {
    class PhiVariable {
        public:
        std::string ID;
        std::string value;
        std::string type;

        PhiVariable(std::string _ID, std::string _value, std::string _type) {
            ID = _ID;
            value = _value;
            type = _type;
        }
    };

    class Parser {
        public:
        AST::AST ast;
        int currentNode;
        
        /*
        * Containers
        */
        std::vector<PhiVariable> variables;
        
        Parser(AST::AST _ast) {
            ast = _ast;
            currentNode = 0;
            variables = {};
        }

        static bool isOperator(std::string text) {
            for (uint8_t i = 0; i < N_OF_OPERATORS; i++) {
                if (OPERATORS[i] == text) {
                    return true;
                }
            }
            return false;
        }
        
        static bool isVariableName(std::string text) {
            return isKeyword(text) || utils::isNumeric(text) ? false : true;
        }
        
        static bool isKeyword(std::string text) {
            for (uint8_t i = 0; i < N_OF_KEYWORDS; i++) {
                if (KEYWORDS[i] == text) {
                    return true;
                }
            }
            return false;
        }

        /*
        * Tries to find an operator, if found, the operator is returned
        */
        static std::string hasOperator(std::string text) {
            for (uint8_t i = 0; i < N_OF_OPERATORS; i++) {
                if (text.find_first_of(OPERATORS[i]) != std::string::npos) {
                    return OPERATORS[i];
                }
            } 
            return "null";
        }
        
        /*
        * returns the index of the variable if found, if not it's returning -1
        */
        int isVariableDefined(std::string variable) {
            for (int i = 0; i < this->variables.size(); i++) {
                if (this->variables[i].ID == variable) {
                    return i;
                }
            }
            return -1;
        }
        
        /*
        * tries to determine the "value"'s type and creates a new variable with this
        * type and this value if the value is understood correctly by the parser
        * then returns the created PhiVariable
        */
        PhiVariable parseVariableValue(std::string variable, std::string value) {
            if (utils::isNumeric(value)) {
                PhiVariable createdVariable = PhiVariable(variable, value, "number");
                this->variables.push_back(createdVariable);
                return createdVariable;
            }
            else if (utils::isString(value)) {
                PhiVariable createdVariable = PhiVariable(variable, value, "string");
                this->variables.push_back(createdVariable);
                return createdVariable;
            }
            else if (utils::isArrayValue(value)) {
                PhiVariable createdVariable = PhiVariable(variable, value, "list");
                this->variables.push_back(createdVariable);
                return createdVariable;
            }
            else if (isVariableName(value)) {
                int valueVariableIndex = this->isVariableDefined(value);
                if (valueVariableIndex != -1) {
                    std::string newVariableValue = this->variables[valueVariableIndex].value;
                    PhiVariable createdVariable = PhiVariable(variable, newVariableValue, "null");
                    this->variables.push_back(createdVariable);
                    return createdVariable;
                } else {
                    utils::closeWithError("Undefined varialbe \"" + value + "\" ");
                }
            }            
            return PhiVariable("null", "null", "null");
        }
        
        void parseVariable(AST::ASTNode variableNode) {
            std::vector<AST::ASTNode> variableChildren = ast.getChildren(variableNode.ID);        
            
            // In case of one operator
            if (variableChildren.size() == 1) {
                if (variableChildren[0].value == "=") {
                    std::vector<AST::ASTNode> variableValue = ast.getChildren(variableChildren[0].ID);
                            
                    // In case of one variable value
                    if (variableValue.size() == 1) {  
                        PhiVariable parsedVarible = parseVariableValue(variableNode.value, variableValue[0].value);
                        std::cout << variableNode.value << " is " << parsedVarible.value << " with type of " << parsedVarible.type << std::endl;
                    }
                }
            }
        }
        
        void parseAST() {
            std::vector<AST::ASTNode> children = ast.getChildren(currentNode);
            
            for (AST::ASTNode child : children) {
                if (isOperator(child.value)) {}
                else if (isVariableName(child.value)) {
                    parseVariable(child);
                }
            }
            
        }

    };
}
