package lexer;

import java.util.List;

import exceptions.*;
import lexer.ast.ASTNode;
import lexer.ast.AbstractSyntaxTree;

public final class PhiLexer {

	private enum LEXER_STATUS {
		FREE,
		IN_COMMENT,
		IN_IF;
	}
	private LEXER_STATUS status;
	private int astNodeLevelID;
	private int astSavedNodeLevelID;
	private final AbstractSyntaxTree ast;  // The Abstract Syntax Tree
	
	public PhiLexer() {
		this.status = LEXER_STATUS.FREE;
		this.ast = new AbstractSyntaxTree();
		this.astNodeLevelID = 0;
		this.astSavedNodeLevelID = 0;
	}
	
	public final boolean tokenizeOperator(String text, final String operatorSign) throws PhiSyntaxError {
		final int operatorID,
				operatorIndex = text.indexOf(operatorSign),
				operatorIndexOffset = operatorSign.length();
		
		if (operatorIndex != -1) {
			final String variableName = text.substring(0, operatorIndex).trim();
						
			if (!Checker.isLeftSideOfOperatorCanBeNonVariable(operatorSign) && !Checker.isVariableNameCorrect(variableName)) {
				throw new PhiSyntaxError("\"" + variableName + "\" could not be used as a variable name", -1);
			}
			
			operatorID = this.ast.createNode(this.ast.createNode(this.astNodeLevelID, variableName), operatorSign);
			final String variableValue = text.substring(operatorIndex + operatorIndexOffset, text.length()).trim();
			this.ast.createNode(operatorID, variableValue);
			
			return true;
		}
		return false;
	}
	
	/**
	 * Lexer makes a parse tree (AST). Finds syntax errors, 
	 * recognize out statements and expressions, save tokens to the AST.
	 * 
	 * @param inputinputLine A line of source code 
	 * @return 1 if successful 0 if not
	 * @throws PhiSyntaxError 
	 */
	public final int tokenize(final String inputinputLine) throws PhiSyntaxError {
		String inputLine = inputinputLine;
		
		/*
		 * Handle comments
		 */
		// Multi line comment
		final int multiLineCommentStartIndex = inputLine.indexOf("\"\"\"");
		if (multiLineCommentStartIndex != -1) {
			if (this.status == LEXER_STATUS.IN_COMMENT) {
				
				// This means the end of the comment
				inputLine = inputLine.substring(multiLineCommentStartIndex + 3, inputLine.length()).trim();
				this.status = LEXER_STATUS.FREE;
			}
			else {
				
				// The start of the comment 
				inputLine = inputLine.substring(0, multiLineCommentStartIndex).trim();
				this.status = LEXER_STATUS.IN_COMMENT;
			}
		} else if (this.status == LEXER_STATUS.IN_COMMENT) {
			
			// Ignore the interior of the comment
			return 1;
		}
		
		// One line comment
		final int commentStartIndex = inputLine.indexOf('#');
		if (commentStartIndex != -1) {
			inputLine = inputLine.substring(0, commentStartIndex).trim();
		}
		
		/*
		 * Handle empty line or whitespace
		 */
		if (inputLine.isEmpty() || inputLine.isBlank()) {
			return 1;
		}
		
		/*
		 * Start looking for syntax and start building AST
		 */
		inputLine = inputLine.trim();
		
		/**
		 * Statements
		 */
		if (Checker.isIfStatement(inputLine)) {
			this.status = LEXER_STATUS.IN_IF;
			
			this.astSavedNodeLevelID = this.astNodeLevelID;
			final int ifNodeID = this.ast.createNode(this.astNodeLevelID, "if");
			
			this.astNodeLevelID = this.ast.createNode(ifNodeID, "condition");
			tokenize(inputLine.replace("if", "").trim());
			
			this.astNodeLevelID = this.ast.createNode(ifNodeID, "body");
			return 1;
		}
		
		if (Checker.isElseIfStatement(inputLine)) {
			if (this.status == LEXER_STATUS.IN_IF) {
				final int elseIfNodeID = this.ast.createNode(this.astNodeLevelID, "elseif");
				
				this.astNodeLevelID = this.ast.createNode(elseIfNodeID, "condition");
				tokenize(inputLine.replace("elseif", "").trim());
				
				this.astNodeLevelID = this.ast.createNode(elseIfNodeID, "body");
				return 1;
			} else {
				throw new PhiSyntaxError("Unexpected token \"elseif\".", -1);
			}
		}
		
		if (inputLine.replaceAll("\\s*", "").equals("else")) {
			if (this.status == LEXER_STATUS.IN_IF) {
				this.astNodeLevelID = this.ast.createNode(this.astNodeLevelID, "else");
			} else {
				throw new PhiSyntaxError("Unexpected token \"else\".", -1);
			}
			return 1;
		}
		
		if (inputLine.replaceAll("\\s*", "").equals("endif")) {
			if (this.status == LEXER_STATUS.IN_IF) {
				this.status = LEXER_STATUS.FREE;
				
				// Restore the last node level before "if"
				this.astNodeLevelID = this.astSavedNodeLevelID; 
			} else {
				throw new PhiSyntaxError("Unexpected token \"endif\".", -1);
			}
			return 1;
		}
		
		/*
		 * Loops
		 */
		// TODO
		
		inputLine = inputLine.replaceAll("\\s*", "");
		
		/**
		 * Operators
		 */
		for (String operator : Checker.OPERATORS) {
			if (tokenizeOperator(inputLine, operator)) {
				return 1;
			}
		}
		
		return 0;
	}
	
	public void print(Object o) {
		System.out.println(o);
	}
	
	public void printAST(int node) {
		print("-------------");
		List<ASTNode> c = this.ast.getChildren(node);
		
		int i = 0;
		while (true) {
			try {
				print(c.get(i));
			} catch (java.lang.IndexOutOfBoundsException e) {
				break;
			} 
			i++;
		}
		print("-------------");
	}
	
}
