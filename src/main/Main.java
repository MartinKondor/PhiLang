/**
 * PhiLang.
 * Copyright (C) Martin Kondor 2019 
 */
package main;

import java.util.ArrayList;
import java.util.List;
import org.apache.commons.cli.CommandLine;

import exceptions.PhiSyntaxError;
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
	 */
	public final static void main(final String[] args) {
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
        	//allLinesInFile.add("_something = 2");
        	//allLinesInFile.add("_something == 2");
        	//allLinesInFile.add("_something != 2");
        	//allLinesInFile.add("_something += 2");
        	//allLinesInFile.add("_something -= 2");
        	//allLinesInFile.add("_something <= 2");
        	//allLinesInFile.add("_something >= 2");
        	//allLinesInFile.add("_something < 2");
        	//allLinesInFile.add("_something > 2");
        	//allLinesInFile.add("_something + 2");
        	//allLinesInFile.add("_something - 2");
        	//allLinesInFile.add("_something * 2");
        	//allLinesInFile.add("_something / 2");
        	
        	/*
        	allLinesInFile.add("if 1 == 1");
        	allLinesInFile.add("	inif1 == 1");
        	allLinesInFile.add("	inif2 == 1");
        	allLinesInFile.add("elseif 3 == 3");
        	allLinesInFile.add("	inelseif1 == 1");
        	allLinesInFile.add("else");
        	allLinesInFile.add("	inelse2 == 1");
        	allLinesInFile.add("endif");
        	allLinesInFile.add("outofif = 1");
        	*/
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
		
		// lexer.printAST(18);
		
		System.out.println("\nFinished in: " + (System.currentTimeMillis() - startTime)/1000 + " seconds");
	}

}
