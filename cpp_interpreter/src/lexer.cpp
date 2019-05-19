#include <iostream>
#include <string>
#include <vector>
#include "utils.cpp"
#include "ast.cpp"
#include "parser.cpp"


namespace Lexer {

enum LEXER_STATUS {
  LEXER_FREE = 0,
  LEXER_IN_IF = 1,
  LEXER_IN_WHILE = 2,
  LEXER_IN_FOR = 3
};

class Lexer {
  public:
  int currentNodeID;
  AST::AST ast;
  LEXER_STATUS lexerStatus;

  Lexer() {
    currentNodeID = 0;
    ast = AST::AST();
    lexerStatus = LEXER_FREE;
  }

  bool lexOperator(const std::string line, const std::string _operator) {
    const int operatorIndex = line.find(_operator);

    if (operatorIndex != std::string::npos) {
      const std::string leftPart = line.substr(0, operatorIndex);
      const std::string rightPart = line.substr(operatorIndex + _operator.length(), line.length());

      const int operatorNodeID = ast.addNode(ast.addNode(currentNodeID, leftPart), _operator);
      const int _savedNodeID = currentNodeID;
      currentNodeID = operatorNodeID;

      lex(rightPart);

      currentNodeID = _savedNodeID;
      return true;
    }
    return false;
  }

  void lex(const std::string line, const unsigned int lineNumber=0) {

    // Remove comments
    // TODO

    // Ignore whitespace
    if (line.find_first_not_of(' ') == std::string::npos) {
      return;
    }

    const std::string lineWithoutSpace = utils::removeSpace(line);
    if (lineWithoutSpace == "pass") return;
    size_t tokenIndex;

    /*
    *  Check for statements
    */
    tokenIndex = line.find("if");
    if (tokenIndex != std::string::npos && utils::hasTheGivenKeyword("if", line)) {
      std::string lineWithoutIf = line.substr(tokenIndex + 2, line.length());
      utils::trim(lineWithoutIf);

      if (lineWithoutIf.find_first_not_of(' ') == std::string::npos) {
          utils::closeWithError("No condition for if", lineNumber);
      }

      const int ifNodeID = ast.addNode(currentNodeID, "if");
      currentNodeID = ast.addNode(ifNodeID, "condition");
      lex(lineWithoutIf);
      currentNodeID = ifNodeID;
      lexerStatus = LEXER_IN_IF;
      return;
    }

    tokenIndex = line.find("elseif");
    if (tokenIndex != std::string::npos && utils::hasTheGivenKeyword("elseif", line)) {
      if (lexerStatus == LEXER_IN_IF) {
        std::string elseIfConditionLine = line.substr(tokenIndex + 6, line.length());
        utils::trim(elseIfConditionLine);

        if (elseIfConditionLine.find_first_not_of(' ') == std::string::npos) {
          utils::closeWithError("No condition for elseif", lineNumber);
        }

        ast.addNode(currentNodeID, "elseif");
        const int savedNodeID = currentNodeID;
        currentNodeID = ast.addNode(currentNodeID, "elseif_condition");
        lex(elseIfConditionLine, lineNumber);
        currentNodeID = savedNodeID;
        return;
      } else {
        utils::closeWithError("Unexpected token \"elseif\"", lineNumber);
      }
    }

    tokenIndex = line.find("endif");
    if (tokenIndex != std::string::npos && utils::hasTheGivenKeyword("endif", line)) {
      if (lexerStatus == LEXER_IN_IF) {
        currentNodeID = ast.getNode(currentNodeID).parentID;

        if (ast.getNode(currentNodeID).value == "while") {
            lexerStatus = LEXER_IN_WHILE;
        }
        if (ast.getNode(currentNodeID).value == "for") {
            lexerStatus = LEXER_IN_FOR;
        }
        else if (ast.getNode(currentNodeID).value != "if") {
            lexerStatus = LEXER_FREE;
        }
        return;
      }
      else {
        utils::closeWithError("Unexpected token \"endif\"", lineNumber);
      }
    }

    tokenIndex = line.find("else");
    if (tokenIndex != std::string::npos && utils::hasTheGivenKeyword("else", line)) {
      if (lexerStatus != LEXER_IN_IF) {
        utils::closeWithError("Unexpected token \"else\"", lineNumber);
      }
      ast.addNode(currentNodeID, "else");
      return;
    }

    tokenIndex = line.find("while");
    if (tokenIndex != std::string::npos && utils::hasTheGivenKeyword("while", line)) {
      std::string lineWithoutWhile = line.substr(tokenIndex + 5, line.length());
      utils::trim(lineWithoutWhile);
      
      if (lineWithoutWhile.find_first_not_of(' ') == std::string::npos) {
        utils::closeWithError("No condition for while", lineNumber);
      }

      const int whileNodeID = ast.addNode(currentNodeID, "while");
      currentNodeID = ast.addNode(whileNodeID, "condition");
      lex(lineWithoutWhile, lineNumber);
      currentNodeID = whileNodeID;
      lexerStatus = LEXER_IN_WHILE;
      return;
    }

    tokenIndex = line.find("endwhile");
    if (tokenIndex != std::string::npos && utils::hasTheGivenKeyword("endwhile", line)) {
      if (lexerStatus == LEXER_IN_WHILE) {
        currentNodeID = ast.getNode(currentNodeID).parentID;

        if (ast.getNode(currentNodeID).value == "if") {
            lexerStatus = LEXER_IN_IF;
        }
        if (ast.getNode(currentNodeID).value == "for") {
            lexerStatus = LEXER_IN_FOR;
        }
        else if (ast.getNode(currentNodeID).value != "while") {
            lexerStatus = LEXER_FREE;
        }
        return;
      }
      else {
        utils::closeWithError("Unexpected token \"endwhile\"", lineNumber);
      }
    }

    tokenIndex = line.find("for");
    if (tokenIndex != std::string::npos && utils::hasTheGivenKeyword("for", line)) {
        std::string lineWithoutFor = line.substr(tokenIndex + 3, line.length());
        utils::trim(lineWithoutFor);
        
        if (lineWithoutFor.find_first_not_of(' ') == std::string::npos) {
          utils::closeWithError("No condition for for", lineNumber);
        }

        const int forNodeID = ast.addNode(currentNodeID, "for");
        currentNodeID = ast.addNode(forNodeID, "condition");
        lex(lineWithoutFor, lineNumber);
        currentNodeID = forNodeID;
        lexerStatus = LEXER_IN_FOR;
        return;
    }

    tokenIndex = line.find("endfor");
    if (tokenIndex != std::string::npos && utils::hasTheGivenKeyword("endfor", line)) {
      if (lexerStatus == LEXER_IN_FOR) {
        currentNodeID = ast.getNode(currentNodeID).parentID;

        if (ast.getNode(currentNodeID).value == "if") {
            lexerStatus = LEXER_IN_IF;
        }
        if (ast.getNode(currentNodeID).value == "while") {
            lexerStatus = LEXER_IN_WHILE;
        }
        else if (ast.getNode(currentNodeID).value != "for") {
            lexerStatus = LEXER_FREE;
        }
        return;
      }
      else {
        utils::closeWithError("Unexpected token \"endfor\"", lineNumber);
      }
    }

    /*
    *  Check for Operators
    */
    for (int i = 0; i < N_OF_OPERATORS; i++) {
      if (lexOperator(lineWithoutSpace, OPERATORS[i])) {
        return;
      }
    }

    ast.addNode(currentNodeID, line);
  }

  ~Lexer() {}
};

}
