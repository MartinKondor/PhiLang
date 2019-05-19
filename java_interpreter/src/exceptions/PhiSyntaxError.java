package exceptions;

public final class PhiSyntaxError extends PhiException {

	private static final long serialVersionUID = 1L;
	
	public PhiSyntaxError(final String cause, final int lineNumber) {
		super(cause, lineNumber);
	}
	
}
