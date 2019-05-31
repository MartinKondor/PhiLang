#include "../source/lexer.cpp"


const bool token_should_behave_as_expected() {
    LEXER::Token token = LEXER::Token("type", "value");
    LEXER::Token null_token = LEXER::Token();
    return token.type == "type" && token.value == "value" &&
            null_token.type == "null" && null_token.value == "null";
}

bool lexer_can_recognize_simple() {

    // Should be all whitespace
    std::string ws_input = " \t\r\n";
    for (int i = 0; i < ws_input.length(); i++) {
        if (!LEXER::Lexer::is_whitespace(ws_input[i])) {
            return false;
        }
    }

    for (std::string keyword : LEXER::KEYWORDS) {
        if (!LEXER::Lexer::is_keyword(keyword)) {
            return false;
        }
    }

    if (LEXER::Lexer::is_keyword("something")) {
        return false;
    }

    return true;
}

bool lexer_throws_err_on_bad_keyword_usage() {
    return false;
}
