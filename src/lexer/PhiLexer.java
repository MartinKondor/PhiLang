package lexer;

import lexer.ast.AbstractSyntaxTree;
import lexer.token.PhiToken;

public class PhiLexer {

	private enum LEXER_STATUS {
		FREE,
		IN_COMMENT;
	}
	private LEXER_STATUS status;
	private AbstractSyntaxTree AST;  // The Abstract Syntax Tree
	
	public PhiLexer() {
		this.status = LEXER_STATUS.FREE;
		this.AST = new AbstractSyntaxTree();
	}
	
	public static boolean isNumeric(String strNum) {
	    try {
	    	double d = Double.parseDouble(strNum);
	    } catch (NumberFormatException | NullPointerException e) {
	        return false;
	    }
	    return true;
	}
	
	/**
	 * @param text Usually a line
	 * @return PhiToken or if the text is empty null
	 */
	public PhiToken tokenize(String inputText) {
		String tokenValue = "null",
				tokenType = "null",
				text = inputText;
		
		/*
		 * Handle comments
		 */
		// Multi line comment
		int multiLineCommentStartIndex = text.indexOf("\"\"\"");
		if (multiLineCommentStartIndex != -1) {
			
			if (this.status == LEXER_STATUS.IN_COMMENT) {
				// This means the end of the comment
				
				text = text.substring(multiLineCommentStartIndex + 3, text.length()).trim();
				this.status = LEXER_STATUS.FREE;
			}
			else {
				// The start of the comment 
				
				text = text.substring(0, multiLineCommentStartIndex).trim();
				this.status = LEXER_STATUS.IN_COMMENT;
			}
		} else if (this.status == LEXER_STATUS.IN_COMMENT) {
			// Ignore the interior of the comment
			
			return null;
		}
		
		// if found a one line comment remove it
		int commentStartIndex = text.indexOf('#');
		if (commentStartIndex != -1) {
			text = text.substring(0, commentStartIndex).trim();
		}
		
		/*
		 * Handle empty line or whitespace
		 */
		if (text.isEmpty() || text.isBlank()) {
			return null;
		}
		
		/*
		 * Primitive types
		 */
		text = text.trim();
		if (PhiLexer.isNumeric(text)) {
			tokenValue = text;
			tokenType = "Number";
		}
		
		/*
		 * Check for built in functions
		 */
		int indexOfBuiltinCall = text.indexOf("print");
		if (indexOfBuiltinCall != -1) {
			
			// Check for parameters
			String parameters[] = text.substring(5, text.length())
					.trim()
					.replace("(", "")
					.replace(")", "")
					.split(",");

			System.out.println("parameters:");
			for (int i = 0; i < parameters.length; i++) {
				parameters[i] = parameters[i].replace(",", "").trim();
				System.out.println(parameters[i]);
			}
			
		}
		
		return new PhiToken(tokenValue, tokenType);
	}

	public AbstractSyntaxTree getAST() {
		return this.AST;
	}

	public void setAST(AbstractSyntaxTree AST) {
		this.AST = AST;
	}
	
}
