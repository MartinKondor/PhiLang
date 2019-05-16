/**
 * Copyright (C) Martin Kondor 2019
 */
package main;

import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.DefaultParser;
import org.apache.commons.cli.HelpFormatter;
import org.apache.commons.cli.Option;
import org.apache.commons.cli.CommandLine;

public class Arguments {
	
	private final Options options;
	private final Option inputFilePath;
	private final Option isVerbose;
	private final CommandLineParser parser;
	private final HelpFormatter formatter;
	
	public Arguments() {
		this.options = new Options();
		this.inputFilePath = new Option("i", "input", true, "input file path");
		this.isVerbose = new Option("v", "verbose", false, "loging everything");
		this.parser = new DefaultParser();
		this.formatter = new HelpFormatter();
		
		inputFilePath.setRequired(true);
		isVerbose.setRequired(false);
		isVerbose.setOptionalArg(false);
		
		// Set command line options
        options.addOption(inputFilePath);
        options.addOption(isVerbose);
	}
	
	/**
	 * @param args Arguments from the command line
	 * @return
	 */
	public CommandLine parse(String[] args) {
		CommandLine cmd = null;
        try {
            cmd = parser.parse(options, args);
        } catch (ParseException e) {
            System.out.println(e.getMessage());
            formatter.printHelp("Phi", options);
            System.exit(1);
        }
        return cmd;
	}
	
}
