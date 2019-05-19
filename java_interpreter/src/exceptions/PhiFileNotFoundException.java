package exceptions;

public final class PhiFileNotFoundException extends PhiException {

	private static final long serialVersionUID = 1L;
	
	public PhiFileNotFoundException(final String cause, final int lineNumber) {
		super(cause, lineNumber);
	}

}
