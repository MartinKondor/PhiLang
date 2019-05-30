#include "../source/lexer.cpp"


const bool token_should_behave_as_expected() {
    Lexer::Token token = Lexer::Token("type", "value");
    return token.type == "type" && token.value == "value";
}

const bool lexer_can_recognize_simple(Lexer::Lexer &lexer) {
    std::vector<std::string> tokens;

    tokens = lexer.lex("0");
    // TODO

    return false;
}

const bool lexer_throws_err_on_bad_keyword_usage(Lexer::Lexer &lexer) {
    return false;
}
