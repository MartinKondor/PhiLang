/*--------------------------------------------

Lexer class.

--------------------------------------------*/
#ifndef _LEXER_HPP_
#define _LEXER_HPP_

#define N_OF_OPERATORS 17
#define N_OF_KEYWORDS 27

namespace Lexer {
    
    const std::string OPERATORS[N_OF_OPERATORS] = {
        "==", "!=", "+=", "-=", "*=", "/=", "%=", ">=", "<=",
        "=", ">", "<", "/", "*", "%", "+", "-",
    };

    const std::string KEYWORDS[N_OF_KEYWORDS] = {
        "if", "else", "elseif", "while", "for", "in",
        "continue", "break", "true", "false", "null",
        "and", "or", "not", "def", "return", "const",
        "try", "catch", "throw", "as", "import", "delete",
        "finally", "is", "pass", "yield"
    };

    class Token {
        public:
        std::string type;
        std::string value;

        Token(std::string type, std::string value);
    };

    class Lexer {
        private:
        std::vector<std::string> lines;

        public:
        Lexer();
        Lexer(std::vector<std::string> lines);

        /**
        * Spliting "line" into the recognized symbols
        * of the language aka "tokens"
        */
        std::vector<std::string> lex(std::string line);
    };

}

#endif
