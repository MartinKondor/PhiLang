package parser;

import java.util.HashMap;
import java.util.List;

import lexer.*;
import lexer.types.*;

public class PhiParser {
	
	PhiLexer lexer;
	
	public PhiParser() {
		this.lexer = new PhiLexer();
	}
	
	public HashMap<String, String> generateParseTreeFromLines(List<String> lines) {
		return null;
	}

	/**
	 * @param text Text to parse, usually it's just a line
	 * @return PhiObject Parsed object
	 */
	public PhiObject parseText(String text) {
		return null;
	}
	
}
