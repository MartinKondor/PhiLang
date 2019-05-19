package lexer;

public class Checker {
    
	public final static String[] KEYWORDS = {
			"if", "else", "elseif", "while", "for", "in",
			"continue", "break", "true", "false", "null",
			"and", "or", "not", "def", "return", "const",
			"try", "catch", "throw", "as", "import", "delete",
			"finally", "is", "pass", "yield"
	};
	public final static String[] OPERATORS = {
			"==", "!=", "+=", "-=", ">=", "<=",
			">", "<", "=", "/", "*", "%",
			"+", "-"
	};
	
    public final static boolean isNumeric(final String strNum) {
	    try {
	    	Double.parseDouble(strNum);
	    } catch (NumberFormatException | NullPointerException e) {
	        return false;
	    }
	    return true;
    }
    
    public final static boolean isVariable(final String text) {
        return isNumeric(String.valueOf(text.charAt(0))) ? false : true;
    }
    
    public final static boolean isKeyword(String text) {
    	for (int i = 0; i < KEYWORDS.length; i++) {
    		if (KEYWORDS[i] == text) {
    			return true;
    		}
    	}
    	return false;
    }
    
    public final static boolean isVariableNameCorrect(final String text) {
    	return text.contains("!") || Checker.isKeyword(text) || isNumeric(String.valueOf(text.charAt(0))) ? false : true;
    }
    
    public final static boolean isLeftSideOfOperatorCanBeNonVariable(final String op) {
    	return op == "==" || op == "!=" || op == ">=" || op == "<=" || op == ">" || op == "<" ? true : false;
    }
    
    private final static boolean hasTheGivenKeyword(final String givenKeyword, final String text) {
    	String inputText = text.trim();
    	if (inputText.startsWith(givenKeyword) && inputText.charAt(givenKeyword.length()) == ' ') {
    		return true;
    	}
    	return false;
    }
    
    public final static boolean isIfStatement(final String text) {
    	return hasTheGivenKeyword("if", text);
    }
    
    public final static boolean isElseIfStatement(final String text) {
    	String inputText = text.trim();
    	if (inputText.startsWith("elseif") && inputText.charAt(6) == ' ') {
    		return true;
    	}
    	return false;
    }
    
    public final static boolean isWhileStatement(final String text) {
    	return hasTheGivenKeyword("while", text);
    }
    
}
