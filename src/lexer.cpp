#ifndef LEXER_CPP_
#define LEXER_CPP_
#endif


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
  bool inComment;

  Lexer() {
    this->currentNodeID = 0;
    this->ast = AST::AST();
    this->lexerStatus = LEXER_FREE;
    this->inComment = false;
  }

  /**
   * Builds an AST node for an operator.
   */
  const bool lexOperator(const std::string &line, const std::string &_operator) {
    const int operatorIndex = line.find(_operator);

    if (operatorIndex != std::string::npos) {

      // Usually a variable name
      const std::string leftPart = line.substr(0, operatorIndex);

      // Usually the variable's value
      const std::string rightPart = line.substr(operatorIndex + _operator.length(), line.length());

      const int operatorNodeID = this->ast.addNode(this->ast.addNode(this->currentNodeID, leftPart), _operator);
      const int _savedNodeID = this->currentNodeID;
      this->currentNodeID = operatorNodeID;
      this->lex(rightPart);
      this->currentNodeID = _savedNodeID;
      return true;
    }
    return false;
  }

  const void lex(const std::string &line, const unsigned int &lineNumber=0) {
      
    /**
    * Multi line comments
    */
    size_t commentIndex;
    commentIndex = line.find_first_of("\"\"\"");
    if (commentIndex != std::string::npos) {
        if (!this->inComment) {
          std::string inputLine = line.substr(0, commentIndex);
          utils::trim(inputLine);
          lex(inputLine, lineNumber);
          this->inComment = true;
          return;
        } else {
          std::string inputLine = line.substr(commentIndex + 3, line.length());
          utils::trim(inputLine);
          this->inComment = false;
          lex(inputLine, lineNumber);
          return;
        }
    }
    else if (this->inComment) {
      return;
    }

    // One line comment
    commentIndex = line.find_first_of("#");
    if (commentIndex != std::string::npos) {
      std::string inputLine = line.substr(0, commentIndex);
      utils::trim(inputLine);
      lex(inputLine);
      return;
    }

    // Ignore whitespace
    if (line.find_first_not_of(' ') == std::string::npos) {
      return;
    }

    /**
    *  pass
    */
    const std::string lineWithoutSpace = utils::removeSpace(line);
    if (lineWithoutSpace == "pass") return;
    size_t tokenIndex;

    /**
    *  if
    */
    tokenIndex = line.find("if");
    if (tokenIndex != std::string::npos && utils::hasTheGivenKeyword("if", line)) {
      std::string lineWithoutIf = line.substr(tokenIndex + 2, line.length());
      utils::trim(lineWithoutIf);

      if (lineWithoutIf.find_first_not_of(' ') == std::string::npos) {
          utils::closeWithError("No condition for if", lineNumber);
      }

      const int ifNodeID = this->ast.addNode(this->currentNodeID, "if");
      this->currentNodeID = this->ast.addNode(ifNodeID, "condition");
      lex(lineWithoutIf);
      this->currentNodeID = ifNodeID;
      this->lexerStatus = LEXER_IN_IF;
      return;
    }

    /**
    *  elseif
    */
    tokenIndex = line.find("elseif");
    if (tokenIndex != std::string::npos && utils::hasTheGivenKeyword("elseif", line)) {
      if (this->lexerStatus == LEXER_IN_IF) {
        std::string elseIfConditionLine = line.substr(tokenIndex + 6, line.length());
        utils::trim(elseIfConditionLine);

        if (elseIfConditionLine.find_first_not_of(' ') == std::string::npos) {
          utils::closeWithError("No condition for elseif", lineNumber);
        }

        this->ast.addNode(this->currentNodeID, "elseif");
        const int savedNodeID = this->currentNodeID;
        this->currentNodeID = this->ast.addNode(this->currentNodeID, "elseif_condition");
        this->lex(elseIfConditionLine, lineNumber);
        this->currentNodeID = savedNodeID;
        return;
      } else {
        utils::closeWithError("Unexpected token \"elseif\"", lineNumber);
      }
    }

    /**
    *  endif
    */
    tokenIndex = line.find("endif");
    if (tokenIndex != std::string::npos && utils::hasTheGivenKeyword("endif", line)) {
      if (this->lexerStatus == LEXER_IN_IF) {
        currentNodeID = this->ast.getNode(this->currentNodeID).parentID;

        if (this->ast.getNode(this->currentNodeID).value == "while") {
            this->lexerStatus = LEXER_IN_WHILE;
        }
        if (this->ast.getNode(this->currentNodeID).value == "for") {
            this->lexerStatus = LEXER_IN_FOR;
        }
        else if (this->ast.getNode(this->currentNodeID).value != "if") {
            this->lexerStatus = LEXER_FREE;
        }
        return;
      }
      else {
        utils::closeWithError("Unexpected token \"endif\"", lineNumber);
      }
    }

    /**
    *  else
    */
    tokenIndex = line.find("else");
    if (tokenIndex != std::string::npos && utils::hasTheGivenKeyword("else", line)) {
      if (this->lexerStatus != LEXER_IN_IF) {
        utils::closeWithError("Unexpected token \"else\"", lineNumber);
      }
      this->ast.addNode(currentNodeID, "else");
      return;
    }

    /**
    *  while
    */
    tokenIndex = line.find("while");
    if (tokenIndex != std::string::npos && utils::hasTheGivenKeyword("while", line)) {
      std::string lineWithoutWhile = line.substr(tokenIndex + 5, line.length());
      utils::trim(lineWithoutWhile);
      
      if (lineWithoutWhile.find_first_not_of(' ') == std::string::npos) {
        utils::closeWithError("No condition for while", lineNumber);
      }

      const int whileNodeID = this->ast.addNode(this->currentNodeID, "while");
      this->currentNodeID = this->ast.addNode(whileNodeID, "condition");
      this->lex(lineWithoutWhile, lineNumber);
      this->currentNodeID = whileNodeID;
      this->lexerStatus = LEXER_IN_WHILE;
      return;
    }

    /**
    *  endwhile
    */
    tokenIndex = line.find("endwhile");
    if (tokenIndex != std::string::npos && utils::hasTheGivenKeyword("endwhile", line)) {
      if (this->lexerStatus == LEXER_IN_WHILE) {
        this->currentNodeID = ast.getNode(this->currentNodeID).parentID;

        if (this->ast.getNode(this->currentNodeID).value == "if") {
            this->lexerStatus = LEXER_IN_IF;
        }
        if (this->ast.getNode(this->currentNodeID).value == "for") {
            this->lexerStatus = LEXER_IN_FOR;
        }
        else if (this->ast.getNode(this->currentNodeID).value != "while") {
            this->lexerStatus = LEXER_FREE;
        }
        return;
      }
      else {
        utils::closeWithError("Unexpected token \"endwhile\"", lineNumber);
      }
    }

    /**
    *  for
    */
    tokenIndex = line.find("for");
    if (tokenIndex != std::string::npos && utils::hasTheGivenKeyword("for", line)) {
        std::string lineWithoutFor = line.substr(tokenIndex + 3, line.length());
        utils::trim(lineWithoutFor);
        
        if (lineWithoutFor.find_first_not_of(' ') == std::string::npos) {
          utils::closeWithError("No condition for for", lineNumber);
        }

        const int forNodeID = this->ast.addNode(this->currentNodeID, "for");
        this->currentNodeID = this->ast.addNode(forNodeID, "condition");
        this->lex(lineWithoutFor, lineNumber);
        this->currentNodeID = forNodeID;
        this->lexerStatus = LEXER_IN_FOR;
        return;
    }

    /**
    *  endfor
    */
    tokenIndex = line.find("endfor");
    if (tokenIndex != std::string::npos && utils::hasTheGivenKeyword("endfor", line)) {
      if (this->lexerStatus == LEXER_IN_FOR) {
        this->currentNodeID = ast.getNode(this->currentNodeID).parentID;

        if (this->ast.getNode(this->currentNodeID).value == "if") {
            this->lexerStatus = LEXER_IN_IF;
        }
        if (this->ast.getNode(this->currentNodeID).value == "while") {
            this->lexerStatus = LEXER_IN_WHILE;
        }
        else if (this->ast.getNode(this->currentNodeID).value != "for") {
            this->lexerStatus = LEXER_FREE;
        }
        return;
      }
      else {
        utils::closeWithError("Unexpected token \"endfor\"", lineNumber);
      }
    }

    /**
    *  Check for Operators
    */
    for (int i = 0; i < N_OF_OPERATORS; i++) {
      if (lexOperator(lineWithoutSpace, OPERATORS[i])) {
        return;
      }
    }

    /**
    *  Add line to the AST by default
    */
    ast.addNode(this->currentNodeID, line);
  }
};

}
