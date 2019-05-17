package exceptions;

public final class PhiIOException extends PhiException {
	
	private static final long serialVersionUID = 1L;
	
	public PhiIOException(final String cause, final int lineNumber) {
		super(cause, lineNumber);
	}
	
}
