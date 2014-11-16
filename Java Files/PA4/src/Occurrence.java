// PA4 Assignment
// Author: Jacob Rede and Anna Beckman
// Date:   11/14/2014
// Class:  CS200
// Email:  anna_beckman@yahoo.com and jare1987@rams.colostate.edu

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
