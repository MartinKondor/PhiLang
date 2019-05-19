#include <iostream>

const uint8_t N_OF_OPERATORS = 14;
const std::string OPERATORS[N_OF_OPERATORS] = {
    "==", "!=", "+=", "-=", ">=", "<=",
    "=", ">", "<", "/", "*", "%", "+", "-",
};

namespace Parser {
    class Variable {
        public:
        std::string ID;
        std::string value;
        std::string type;

        Variable(std::string _ID, std::string _value, std::string _type) {
            ID = _ID;
            value = _value;
            type = _type;
        }
    };

    class Parser {
        public:
        static bool isOperator(std::string text) {
            for (uint8_t i = 0; i < N_OF_OPERATORS; i++) {
                if (OPERATORS[i] == text) {
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
    };
}
