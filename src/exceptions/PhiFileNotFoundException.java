package exceptions;

public class PhiFileNotFoundException extends PhiException {

	public PhiFileNotFoundException(String cause, int lineNumber) {
		super(cause, lineNumber);
	}

}
