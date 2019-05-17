package lexer;

public class Checker {
    
    public static boolean isNumeric(String strNum) {
	    try {
	    	double d = Double.parseDouble(strNum);
	    } catch (NumberFormatException | NullPointerException e) {
	        return false;
	    }
	    return true;
    }
    
    public static boolean isVariable(String text) {
        return isNumeric(text.charAt(0)) ? false : true;
    }
    
}
