// PA3 Assignment
// Author: Alex Eibner and Jacob Rede
// Date:   9/17/2014
// Class:  CS200
// Email:  alexeibner@gmail.com	and jare1987@rams.colostate.edu

public class Occurrence {
	
	private String docName;
	private int termFrequency;
	
	public Occurrence(String name) {
		
		docName = name;
		termFrequency = 1;
		
	}
	
	 public void incFrequency() {
		 
		 termFrequency++;
		 
	 }
	 
	 public String getDocName() {
		 
		 return this.docName;
		 
	 }
	 
	 public int getTermFrequency() {
		 
		 return this.termFrequency;
		 
	 }
	 
}
