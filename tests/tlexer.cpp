
bool testVariableDeclaration(const std::vector<std::string> &lines) {
    Lexer::Lexer lexer = Lexer::Lexer();
    for (int i = 0; i < lines.size(); i++) {
        lexer.lex(lines[i]);
    }
    int a = 0;
    if (lexer.ast.getChildren(a)[0].value != "var") {
        return false;
    }
    if (lexer.ast.getChildren(lexer.ast.getChildren(a)[0].parentID)[0].value != "=") {
        return false;
    }
    if (lexer.ast.getChildren(lexer.ast.getChildren(lexer.ast.getChildren(a)[0].parentID)[0].parentID)[0].value != "0") {
        return false;
    }
    return false;
}

bool testVariableRedeclaration(const std::vector<std::string> &lines) {
    Lexer::Lexer lexer = Lexer::Lexer();
    for (int i = 0; i < lines.size(); i++) {
        lexer.lex(lines[i]);
    }
    return false;
}

bool testIfConditionFalse(const std::vector<std::string> &lines) {
    Lexer::Lexer lexer = Lexer::Lexer();
    for (int i = 0; i < lines.size(); i++) {
        lexer.lex(lines[i]);
    }
    return false;
}

void testLexing() {
    std::vector<std::string> lines = {};
    std::string res = "";
    
    lines.push_back("var = 0");
    res = testVariableDeclaration(lines) ? "+" : "-";
    std::cout << "testVariableDeclaration: " << res << std::endl;
    
    lines.push_back("var = 1");
    res = testVariableRedeclaration(lines) ? "+" : "-";
    std::cout << "testVariableRedeclaration: " << res << std::endl;
    
    lines.push_back("if var == var");
    lines.push_back("   inif = 1");
    lines.push_back("else");
    lines.push_back("   inif = 0");
    lines.push_back("endif");
    res = testIfConditionFalse(lines) ? "+" : "-";
    std::cout << "testIfConditionFalse: " << res << std::endl;
}
