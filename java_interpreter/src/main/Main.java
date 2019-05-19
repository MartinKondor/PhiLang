/**
 * PhiLang.
 * Copyright (C) Martin Kondor 2019 
 */
package main;

import java.util.ArrayList;
import java.util.List;
import org.apache.commons.cli.CommandLine;

import exceptions.PhiSyntaxError;
import lexer.LEXER_COMMENT_STATUS;
import lexer.LEXER_STATUS;
import lexer.PhiLexer;

/**
 * @author Martin Kondor
 * @version 2019.06.prototype
 * @java 11
 */
public final class Main {
	
	public final static String PHI_VERSION = "2019.06.prototype";

	/**
	 * Usage:
	 * 
	 * phi -i [inputFileName]
	 * 
	 * @param args
	 * @throws PhiSyntaxError 
	 */
	public final static void main(final String[] args) throws PhiSyntaxError {
        // For testing
		final double startTime = System.currentTimeMillis();
		
		// Parse in commands
		final CommandLine commandLineCommands = new Arguments().parse(args);
        final String inputFilePath = commandLineCommands.getOptionValue("input");
        final boolean isVerbose = commandLineCommands.hasOption("verbose");
        
        // Start by reading from file
        List<String> allLinesInFile = new ArrayList<String>();
		/*
        try {
			allLinesInFile = PhiFileReader.readInFile(inputFilePath);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			new PhiFileNotFoundException("\"" + inputFilePath + "\" file not found", 0);
			System.exit(1);
		} catch (IOException e) {
			e.printStackTrace();
			new PhiIOException("An error occurred while reading from file: \"" + inputFilePath + "\"", 0);
			System.exit(1);
		}
		*/
        
        // For performance testing
        for (int i = 0; i < 1; i++) {
        	allLinesInFile.add("if 1 == 1");
        	allLinesInFile.add("	insideFirstIf = 0");
        	allLinesInFile.add("	if 1 == 1");
        	allLinesInFile.add("		insideSecondIf = 0");
        	allLinesInFile.add("		if 1 == 1");
        	allLinesInFile.add("			insideThirdIf = 0");
        	allLinesInFile.add("		endif");
        	allLinesInFile.add("		insideSecondIf_2 = 0");
        	allLinesInFile.add("	endif");
        	allLinesInFile.add("	insideFirstIf_2 = 0");
        	allLinesInFile.add("endif");
        	allLinesInFile.add("");
        	allLinesInFile.add("out = 0");
        }
	
		final PhiLexer lexer = new PhiLexer();
		for (int i = 0; i < allLinesInFile.size(); i++) {
			try {
				lexer.tokenize(allLinesInFile.get(i));
			} catch (PhiSyntaxError e) {
				e.printStackTrace();
				System.exit(1);
			}
		}
		
		lexer.printAST(0);
		print(lexer.ast.getNode("insideFirstIf_2"));
		
		/*
		if (lexer.getLexerCommentStatus() == LEXER_COMMENT_STATUS.IN_COMMENT) {
			throw new PhiSyntaxError("Error:\n\tEnd of multi line comment expected.", -1);
		} else if (lexer.getLexerStatus() == LEXER_STATUS.IN_IF) {
			throw new PhiSyntaxError("Error:\n\tEnd of if statement expected.", -1);
		}
		*/	
		
		System.out.println("\nFinished in: " + (System.currentTimeMillis() - startTime)/1000 + " seconds");
	}
	
	public static void print(Object o) {
		System.out.println(o);
	}

}
