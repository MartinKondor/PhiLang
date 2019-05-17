package exceptions;

public abstract class PhiException extends Exception {
	
	private static final long serialVersionUID = 1L;

	public PhiException(final String cause, final int lineNumber) {
		System.out.println(cause);
		System.out.println("At line: " + lineNumber);
	}
	
}
