#include "../source/lexer.cpp"


bool token_should_behave_as_expected() {
    LEXER::Token token = LEXER::Token("type", "value");
    LEXER::Token null_token = LEXER::Token();
    return token.type == "type" && token.value == "value" &&
            null_token.type == "null" && null_token.value == "null";
}

bool lexer_wproperly() {
    PARSER::InputStream is = PARSER::InputStream("");
    LEXER::Lexer lexer = LEXER::Lexer(is);

    // TODO
    
    return false;
}

bool lexer_can_recognize_simple() {

    // Should be all whitespace
    std::string ws_input = " \t\r\n";
    for (int i = 0; i < ws_input.length(); i++) {
        if (!LEXER::Lexer::is_whitespace(ws_input[i])) {
            return false;
        }
    }

    // Should all be keywords
    for (std::string keyword : LEXER::KEYWORDS) {
        if (!LEXER::Lexer::is_keyword(keyword)) {
            return false;
        }
    }
    if (LEXER::Lexer::is_keyword("something")) {
        return false;
    }

    if (!LEXER::Lexer::is_digit('0') || LEXER::Lexer::is_digit('a')) {
        return false;
    }

    // Should all be operators
    for (std::string op : LEXER::OPERATORS) {
        if (!LEXER::Lexer::is_operator(op)) {
            return false;
        }
    }
    if (LEXER::Lexer::is_operator("0")) {
        return false;
    }

    // punctuation
    if (!LEXER::Lexer::is_punc('(') || !LEXER::Lexer::is_punc(')') ||
        !LEXER::Lexer::is_punc('[') || !LEXER::Lexer::is_punc(']')) {
        return false;
    }
    if (LEXER::Lexer::is_punc('a')) {
        return false;
    }

    return true;
}

bool lexer_can_recognize_var() {
    return LEXER::Lexer::is_id("a12") &&
            !LEXER::Lexer::is_id("12") &&
            !LEXER::Lexer::is_id(" ");
}

bool lexer_can_recognize_func() {
    return LEXER::Lexer::is_def("def a()") &&
            LEXER::Lexer::is_def("def a") &&
            LEXER::Lexer::is_def("def a param1, param2") &&
            LEXER::Lexer::is_def("def a(param1, param2)") &&
            !LEXER::Lexer::is_def("adef = 10");
}
