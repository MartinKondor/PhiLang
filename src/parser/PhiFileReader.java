package parser;

import java.util.ArrayList;
import java.util.List;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.FileNotFoundException;

public class PhiFileReader {
	
	public static List<String> readInFile(String pathToFileArg) throws FileNotFoundException, IOException {
		String pathToFile = pathToFileArg;
		if (pathToFile.charAt(0) != '/') {
			pathToFile = System.getProperty("user.dir") + "/" + pathToFile;
		}
		
		File inputFile = new File(pathToFile);
		if (!inputFile.exists()) {
			throw new FileNotFoundException();
		}
		
		List<String> allLinesInFile = new ArrayList<String>();
		BufferedReader reader = new BufferedReader(new FileReader(pathToFile));
        String line;
        
        while ((line = reader.readLine()) != null) {
        	allLinesInFile.add(line);
        } 
        reader.close();
        
		return allLinesInFile;
	}
	
}
