/*--------------------------------------------

Lexer class.

--------------------------------------------*/
#ifndef _LEXER_HPP_
#define _LEXER_HPP_

#define N_OF_OPERATORS 17
#define N_OF_KEYWORDS 27


namespace LEXER {

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

        Token();
        Token(std::string &type, std::string &value);
    };

    class Lexer {
        private:
        Token current_token;
        PARSER::InputStream input_stream;

        public:
        static bool is_whitespace(const char &ch);
        static bool is_keyword(const std::string &input);
        static bool is_digit(const char &ch);
        static bool is_operator(const std::string &input);
        static bool is_punc(const char &ch);  // punctuation
        static bool is_id(const std::string &input);
        static bool is_def(const std::string &input);

        Lexer(PARSER::InputStream input_stream);
        const std::string read_while(bool (*)(char ch));
    };

}

#endif  // _LEXER_HPP_
