#include <iostream>
#include <fstream>
#include <ctime>
#include "lexer.cpp"
using namespace std;

int main(const int argc, const char** args) {
  clock_t begin = clock();

  if (argc < 2) {
    cout << "No input file provided." << endl << "Phi stops.";
    return 1;
  }

  const char* inputFilePath = args[1];
  Lexer::Lexer lexer = Lexer::Lexer();

  string line;
  ifstream myfile(inputFilePath);
  
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      lexer.lex(line);
    }
    myfile.close();
  }
  else {
	  cout << "Unable to open input file \"" << args[1] << "\"" << endl << "Phi stops.";
  } 

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

  Parser::Parser parser = Parser::Parser(lexer.ast);
  parser.parseAST();

  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << endl << "Finished in: " << elapsed_secs << " seconds"; 
  return 0;
}
