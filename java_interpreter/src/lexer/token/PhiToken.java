package lexer.token;

import java.util.HashMap;

public class PhiToken {

	private String value;
	private String type;
	
	public PhiToken(String value, String type) {
		this.value = value;
		this.type = type;
	}
	
	public String toString() {
		return "Value: " + this.value + ", Type: " + this.type + "\n-----";
	}
	
	public String getValue() {
		return value;
	}

	public void setValue(String value) {
		this.value = value;
	}

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}
	
}
