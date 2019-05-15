package exceptions;

public abstract class PhiException {
	
	public PhiException(String cause, int lineNumber) {
		System.out.println(cause);
		System.out.println("At line: " + lineNumber);
	}
	
}
