/**
 * PhiLang.
 * Copyright (C) Martin Kondor 2019 
 */
package main;

import java.io.FileNotFoundException;
import java.io.IOException;
import org.apache.commons.cli.CommandLine;
import java.util.List;

import main.Arguments;
import parser.PhiFileReader;
import exceptions.PhiFileNotFoundException;
import exceptions.PhiIOException;
import lexer.PhiLexer;

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
        List<String> allLinesInFile = null;
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
        
		if (isVerbose) {
			System.out.println("Content of the " + inputFilePath + " file:");
	        for (int i = 0; i < allLinesInFile.size(); i++) {
	        	System.out.println("Line " + i + ": " + allLinesInFile.get(i));
	        }
	        System.out.println();
		}
		
		// Lexing each line
		PhiLexer lexer = new PhiLexer();
		
		for (int i = 0; i < allLinesInFile.size(); i++) {
        	System.out.println(lexer.tokenize(allLinesInFile.get(i)));
        }
	}

}
