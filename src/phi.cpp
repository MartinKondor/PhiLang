#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include "utils.cpp"
#include "ast.cpp"
#include "lexer.cpp"
#include "phiobjects.cpp"
#include "parser.cpp"
using namespace std;


int main(const int argc, const char** args) {
  clock_t begin = clock();
  
  const char* inputFilePath;
  Lexer::Lexer lexer;

  /**
   * Handle command line arguments
   */
  if (argc < 2) {
    cout << "No input file provided." << endl << "Phi stops.";
    return 1;
  }

  inputFilePath = args[1];
  lexer = Lexer::Lexer();

  /**
   * Reading the input file line by line
   */
  string line;
  ifstream inputFile(inputFilePath);
  
  if (inputFile.is_open()) {
    while (getline(inputFile, line)) {
      /**
       * Lexing each line
       */
      lexer.lex(line);
    }
    inputFile.close();
  } else {
	utils::closeWithError("Unable to open input file.");
    exit(1);
  } 

  /**
   *  Catch unclosed statements
   */
  switch (lexer.lexerStatus) {
    case 1:
      utils::closeWithError("Unclosed if statement.");
      break;
    case 2:
      utils::closeWithError("Unclosed while statement.");
      break;
    case 3:
      utils::closeWithError("Unclosed for statement.");
      break;
    default: break;
  }

  /**
  *  Parse in the lexer's AST
  */
  Parser::Parser parser = Parser::Parser(lexer.ast);
  parser.parseAST();

  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << endl << "Finished in: " << elapsed_secs << " seconds";
  
  return 0;
}
