// PA2 Assignment
// Author: Alex Eibner and Jacob Rede
// Date:   9/17/2014
// Class:  CS200
// Email:  alexeibner@gmail.com	and jare1987@rams.colostate.edu

import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class P1 {

	public static ArrayList<String> words = new ArrayList<String>();

	public void readFile(String fileName) {

		try {
			
			// Removes any extra punctuation, whitespace, returns, etc. while reading the input
			Scanner fileScanner = new Scanner(new File(fileName)).useDelimiter("[(\n\r\"\\/=+%$#@^&*~`_|;: *-,!?.)]+");

			while (fileScanner.hasNext()) {

				String tempWord = fileScanner.next().toLowerCase();

				// Removes any HTML codes within the input
				if (tempWord.charAt(0) == '<') {

					fileScanner.next();

					// Iterates through and removes all of the HTML within the brackets
					while (fileScanner.hasNext()) {

						tempWord = fileScanner.next();

						// Stops iterating once it has reached the end of the command
						if (tempWord.charAt(tempWord.length() - 1) == '>') {
							
							break;

						}

					}

					continue;

				}

				if (!tempWord.isEmpty()) {

					int location = binarySearch(tempWord);

					if (location > -1) {

						words.add(location, tempWord);

					}

				}

			}

			if (words.isEmpty()) {

				throw new Exception("ArrayList empty");

			}
			
			fileScanner.close();
			
		} catch (Exception e) {
			
			System.out.println("Error: While reading file line by line: "+ e.getMessage());
			
		}

		System.out.println("WORDS");
		
		for (int j = 0; j < words.size(); j++) {
			
			System.out.println(words.get(j));
			
		}
		
		System.out.println();
		System.out.println("NUMBER OF WORDS: " + words.size());

	}

	public static int binarySearch(String key) {
		
		int first = 0;
		
		// First time searching
		if (words.size() == 0) {
			
			return 0;
			
		}
		
		int length = words.size();
		int mid = 0;
		
		while (first < length) {
		
			mid = (first + length) / 2;
			
			if (key.compareTo(words.get(mid)) < 0) {
				
				// Repeat search in bottom half
				length = mid; 
				
			} else if (key.compareTo(words.get(mid)) > 0) {
				
				// Repeat search in top half
				first = mid + 1; 
				
			} else if (key.compareTo(words.get(mid)) == 0) {
				
				// Found and now do nothing since it already exists
				return -1;
				
			}
			
		}

		mid = (first + length) / 2;
		return mid;
		
	}
	
	public static void main(String[] args) {

		P1 p1 = new P1();
		
		// Checks if an argument is given
		if(args.length <= 0) {
			
			System.out.println("Error: No argument is given.");
			System.exit(0);
			
		} else {
			
			p1.readFile(args[0]);
			
		}
		
	}
	
}
