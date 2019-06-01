/*--------------------------------------------

Parser is responsible for:
* Syntax analysis using the rules of the lexer

--------------------------------------------*/
#ifndef _PARSER_HPP_
#define _PARSER_HPP_


namespace PARSER {

    class InputStream {
        private:
        std::string input;
        int current_pos;  // saves the current position on the stream
        int line_number;
        int line_column;

        public:
        InputStream();
        InputStream(std::string line);
        
        /**
         * returns the next char and removes it from the stream
         */
        char next();

        /**
         * returns the next char without removing from it from the stream
         */
        char peek();

        /**
         * Is it the end of the stream?
         */
        bool is_eof();

        /**
         * Throw error with line info
         */
        void croak(std::string msg);
    };

    class Parser {
        public:

        Parser();
    };

}

#endif

