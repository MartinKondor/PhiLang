package lexer.types;

public abstract class PhiObject {
	
	public abstract String toString();
	
	/*
	 * Called when "PhiObject" is turning to be a PhiString
	 */
	public abstract String __str__();
	
	/*
	 * Called when "PhiObject + other"
	 */
	public abstract PhiObject __add__(PhiObject self, PhiObject other);
	
	/*
	 * Called when "PhiObject - other"
	 */
	public abstract PhiObject __subtraction__(PhiObject self, PhiObject other);
	
	/*
	 * Called when "PhiObject * other"
	 */
	public abstract PhiObject __multiply__(PhiObject self, PhiObject other);
	
	/*
	 * Called when "PhiObject / other"
	 */
	public abstract PhiObject __divided__(PhiObject self, PhiObject other);
	
	/*
	 * Called when "other / PhiObject"
	 */
	public abstract PhiObject __dividing__(PhiObject self, PhiObject other);
	
}
