/**
 * PhiLang.
 * Copyright (C) Martin Kondor 2019 
 */
package main;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.apache.commons.cli.CommandLine;

import exceptions.*;
import parser.PhiFileReader;
import lexer.PhiLexer;
import lexer.token.PhiToken;

/**
 * @author Martin Kondor
 * @version 0.1
 */
public class Main {
	
	public static final String PHI_VERSION = "0.1";

	public static void main(String[] args) {
        
		// Parse in commands
		CommandLine commandLineCommands = new Arguments().parse(args);
        final String inputFilePath = commandLineCommands.getOptionValue("input");
        final boolean isVerbose = commandLineCommands.hasOption("verbose");
        
        if (isVerbose) {
        	System.out.println("Arguments:");
        	System.out.println("-i: " + inputFilePath);
        	System.out.println();
        }
        
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
        
        allLinesInFile.add("\"\"\"");
        allLinesInFile.add("Multi line comment");
        allLinesInFile.add("\"\"\"");
        allLinesInFile.add("");
        allLinesInFile.add("print(10)");
        allLinesInFile.add("print 1, 10, 100");
        allLinesInFile.add("print 10");
        allLinesInFile.add("print(10)");
        allLinesInFile.add("print(1, 10, 100)");
        
		
		/*
		 * Lexing of each line while the lexer build's an AST
		 */
		PhiLexer lexer = new PhiLexer();
		for (int i = 0; i < allLinesInFile.size(); i++) {
			PhiToken token = lexer.tokenize(allLinesInFile.get(i));
			
			if (token != null) {
				System.out.println(token);
			}
			
		}
		
	}

}
