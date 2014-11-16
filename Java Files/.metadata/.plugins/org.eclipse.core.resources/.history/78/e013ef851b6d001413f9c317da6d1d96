// PA3 Assignment
// Author: Alex Eibner and Jacob Rede
// Date:   9/17/2014
// Class:  CS200
// Email:  alexeibner@gmail.com	and jare1987@rams.colostate.edu

import java.util.LinkedList;

public class Term {
	
	public LinkedList<Occurrence> docList = new LinkedList<Occurrence>();
	private int docFrequency;
	private int totalFrequency;
	private String word;
	
	public Term(String name) {
		
		word = name.toLowerCase();
		docFrequency = 0;
		//totalFrequency = 1;
		
	}
	 
	public void incFrequency(String document) {
		
//		if (docList.isEmpty()) {//nothing has been added yet
//			Occurrence newOcc = new Occurrence(document);
//			this.docList.add(newOcc);
//			this.docFrequency++;
//		} else {//LL has items in it
			
			// If docList is not empty, we loop through all items in the linked list looking for an Occurrence object with same name.
			// This will turn true if Occurrence object exists in the linked list.
			boolean OccExists = false;
			
			for(int j = 0; j < docList.size(); j++) {
				
				if (docList.get(j).getDocName().equals(document)) {
					
					// If Occurrence object in the linked list, and has an equal name to the document, we increase the frequency of that occurrence.
					// this.docFrequency++;
					docList.get(j).incFrequency();
					OccExists = true;
					
				}
				
			}
			
			// If the loop did not find a docname that equals our local document.
			// If OCCurrence object was not changed to true, then we need to add an Occurrence to the linked list.
			if (!OccExists) {
				
				Occurrence newOcc = new Occurrence(document);
				this.docList.add(newOcc);
				this.docFrequency++;
				
			}
			
	//	}
		totalFrequency++;
		
	}
	
	public String getWord() {
		
		return this.word;
		
	}
	
	public int getDocFrequency() {
		
		return this.docFrequency;
		
	}
	
	public int getTotalFrequency() {
		
		return this.totalFrequency;
		
	}
	
	/*
	 * This compareTo method gets a Term object as well as an integer that specifies what to return (Either the compare of words or the compare of totalfrequency).
	 */
	public int compareTo(Term compareTerm, int selectionToCompare) {
		
		if (selectionToCompare == 1) {
			
			return this.word.compareTo(compareTerm.word);
			
		} else {
			
			// Compares totalFrequency.
			return Integer.compare(this.totalFrequency, compareTerm.totalFrequency);
			
		}
		
	}
	//new PA3 test class, only used for testing, prints out everything in this object
	public void printTest() {
		System.out.println("Term word: "+this.getWord());
		System.out.print("DocList: ");
		for(int j = 0; j < docFrequency;j++) {
			System.out.print(docList.get(j).getDocName()+", ");
		}
		System.out.println();
	}
	
}