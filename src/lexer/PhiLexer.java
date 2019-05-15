package lexer;

import lexer.types.*;

public class PhiLexer {

	/*
	 * // Whitespace
	NEWLINE            : '\r\n' | 'r' | '\n' ;
	WS                 : [\t ]+ ;
	 
	// Keywords
	VAR                : 'var' ;
	 
	// Literals
	INTLIT             : '0'|[1-9][0-9]* ;
	DECLIT             : '0'|[1-9][0-9]* '.' [0-9]+ ;
	 
	// Operators
	PLUS               : '+' ;
	MINUS              : '-' ;
	ASTERISK           : '*' ;
	DIVISION           : '/' ;
	ASSIGN             : '=' ;
	LPAREN             : '(' ;
	RPAREN             : ')' ;
	 
	// Identifiers
	ID                 : [_]*[a-z][A-Za-z0-9_]* ;
	 */
	
	public PhiLexer() {}
	
	public PhiObject tokenize(String line) {
		return new PhiNumber(0);
	}
	
}
