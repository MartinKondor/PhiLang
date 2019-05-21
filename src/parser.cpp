#ifndef PARSER_CPP_
#define PARSER_CPP_
#endif

using PhiObjects::PhiObject;

namespace Parser {

    class Parser {
        public:
        AST::AST ast;
        int currentNode;
        
        /*
        * Containers
        */
        std::vector<PhiObject> variables;
        
        Parser(const AST::AST &ast) {
            this->ast = ast;
            this->currentNode = 0;
            this->variables = {};
        }

        const static bool isNumeric(const std::string &s) {
            std::string::const_iterator it = s.begin();
            while (it != s.end() && std::isdigit(*it)) ++it;
            return !s.empty() && it == s.end();
        }
        
        const static bool isString(const std::string &text) {
            std::string inputText = text;
            utils::trim(inputText);
            if (inputText[0] == '"' && inputText[inputText.length() - 1] == '"') {
                return true;
            }
            return false;
        }
        
        const static bool isArrayValue(const std::string &text) {
            std::string inputText = text;
            utils::trim(inputText);
            if (inputText[0] == '[' && inputText[inputText.length() - 1] == ']') {
                return true;
            }
            return false;
        }

        const static bool isOperator(const std::string &text) {
            for (uint8_t i = 0; i < N_OF_OPERATORS; i++) {
                if (OPERATORS[i] == text) {
                    return true;
                }
            }
            return false;
        }
        
        const static bool isVariableName(const std::string &text) {
            return Parser::isKeyword(text) || Parser::isNumeric(text) ? false : true;
        }
        
        const static bool isKeyword(const std::string &text) {
            for (uint8_t i = 0; i < N_OF_KEYWORDS; i++) {
                if (KEYWORDS[i] == text) {
                    return true;
                }
            }
            return false;
        }

        /**
        * Tries to find an operator, if found, the operator is returned
        */
        const static std::string hasOperator(const std::string &text) {
            for (uint8_t i = 0; i < N_OF_OPERATORS; i++) {
                if (text.find_first_of(OPERATORS[i]) != std::string::npos) {
                    return OPERATORS[i];
                }
            } 
            return "null";
        }
        
        /**
        * Returns the index of the variable if found in this->variables,
        * if not it's returning -1
        */
        const int isVariableDefined(const std::string &variable) {
            for (int i = 0; i < this->variables.size(); i++) {
                if (this->variables[i].ID == variable) {
                    return i;
                }
            }
            return -1;
        }
        
        /**
        * Attempts to create a new variable with the given variableName and variableValue
        */
        const PhiObject parseVariableValue(const std::string &variableName, const std::string &variableValue) {
            if (this->isNumeric(variableValue)) {
                PhiObject createdVariable = PhiObject(variableName, variableValue, "number");
                this->variables.push_back(createdVariable);
                return createdVariable;
            }
            else if (this->isString(variableValue)) {
                PhiObject createdVariable = PhiObject(variableName, variableValue, "string");
                this->variables.push_back(createdVariable);
                return createdVariable;
            }
            else if (this->isArrayValue(variableValue)) {
                PhiObject createdVariable = PhiObject(variableName, variableValue, "list");
                this->variables.push_back(createdVariable);
                return createdVariable;
            }
            else if (this->isVariableName(variableValue)) {
                int valueVariableIndex = this->isVariableDefined(variableValue);
                if (valueVariableIndex != -1) {
                    
                    std::string newVariableValue = this->variables[valueVariableIndex].value;
                    PhiObject createdVariable = PhiObject(variableName, newVariableValue, "null");
                    this->variables.push_back(createdVariable);
                    
                    return createdVariable;
                } else {
                    utils::closeWithError("Undefined variable \"" + variableValue + "\" ");
                }
            }            
            return PhiObject("null", "null", "null");
        }

        /**
         * If the value is a variable this function returns the PhiObject else
         * it returns the value's created PhiObject.
         * 
         * Example:
         *  resolveValue(1) -> PhiObject("null", "1", "number")
         *  resolveValue(a) -> PhiObject("a", "...", "...")  // If a is defined else it's an error
         */
        const PhiObject resolveValue(const std::string &value) {
            if (this->isNumeric(value)) {
                return PhiObject("null", value, "number");
            }
            else if (this->isString(value)) {
                return PhiObject("null", value, "string");
            }
            else if (this->isArrayValue(value)) {
                return PhiObject("null", value, "list");
            }
            else {
                int rightPartIndex = this->isVariableDefined(value);
                if (rightPartIndex == -1) {
                    utils::closeWithError("Undefined variable \"" + value + "\" ");
                } else {
                    return this->variables[rightPartIndex];
                }
            }
            return PhiObject("null", "null", "null");
        }
        
        /**
        * Parse in a variable + operator + variable|value expression
        */
        const void parseVariable(const AST::ASTNode &variableNode) {
            const std::vector<AST::ASTNode> variableChildren = this->ast.getChildren(variableNode.ID);        
            
            // In case of one operator
            if (variableChildren.size() == 1) {

                /**
                 * Operators
                 */
                if (variableChildren[0].value == "=") {

                    // The left part of the 
                    // variableNode = variableValue[0]
                    const std::vector<AST::ASTNode> variableValue = this->ast.getChildren(variableChildren[0].ID);
                            
                    // In case of one variable value
                    if (variableValue.size() == 1) {  
                        PhiObject parsedVariable = this->parseVariableValue(variableNode.value, variableValue[0].value);
                        std::cout << variableNode.value << " has the value of " << parsedVariable.value << " with type of " << parsedVariable.type << std::endl;
                    }
                }
                else if (variableChildren[0].value == "==") {
                    const std::vector<AST::ASTNode> otherValue = this->ast.getChildren(variableChildren[0].ID);

                    if (otherValue.size() == 1) {
                        PhiObject rightPart = resolveValue(variableNode.value),
                                leftPart = resolveValue(otherValue[0].value);
                        std::cout << rightPart.value << " == " << leftPart.value << " will be " << rightPart.__isEqual__(leftPart) << std::endl;
                    }
                }
                else if (variableChildren[0].value == "+=") {
                    const std::vector<AST::ASTNode> otherValue = this->ast.getChildren(variableChildren[0].ID);

                    PhiObject rightPart = resolveValue(variableNode.value),
                            leftPart = resolveValue(otherValue[0].value);
                    std::cout << rightPart.value << " += " << leftPart.value << " will be " << rightPart.__plus__(leftPart).value << std::endl;
                }
                else if (variableChildren[0].value == "-=") {
                    const std::vector<AST::ASTNode> otherValue = this->ast.getChildren(variableChildren[0].ID);

                    PhiObject rightPart = resolveValue(variableNode.value),
                            leftPart = resolveValue(otherValue[0].value);
                    std::cout << rightPart.value << " -= " << leftPart.value << " will be " << rightPart.__minus__(leftPart).value << std::endl;
                }
                else if (variableChildren[0].value == "*=") {
                    const std::vector<AST::ASTNode> otherValue = this->ast.getChildren(variableChildren[0].ID);

                    PhiObject rightPart = resolveValue(variableNode.value),
                            leftPart = resolveValue(otherValue[0].value);
                    std::cout << rightPart.value << " *= " << leftPart.value << " will be " << rightPart.__star__(leftPart).value << std::endl;
                }
                else if (variableChildren[0].value == "/=") {
                    const std::vector<AST::ASTNode> otherValue = this->ast.getChildren(variableChildren[0].ID);

                    PhiObject rightPart = resolveValue(variableNode.value),
                            leftPart = resolveValue(otherValue[0].value);
                    std::cout << rightPart.value << " /= " << leftPart.value << " will be " << rightPart.__slash__(leftPart).value << std::endl;
                }
                else if (variableChildren[0].value == "%=") {
                    const std::vector<AST::ASTNode> otherValue = this->ast.getChildren(variableChildren[0].ID);

                    PhiObject rightPart = resolveValue(variableNode.value),
                            leftPart = resolveValue(otherValue[0].value);
                    std::cout << rightPart.value << " %= " << leftPart.value << " will be " << rightPart.__modulo__(leftPart).value << std::endl;
                }

            }
        }
        
        /**
         *  Parse the whole stored AST
         */
        const void parseAST() {
            std::vector<AST::ASTNode> children = this->ast.getChildren(currentNode);
            
            for (AST::ASTNode child : children) {
                if (this->isOperator(child.value)) {}
                else if (this->isVariableName(child.value)) {
                    this->parseVariable(child);
                }
            }
        }

    };
}
