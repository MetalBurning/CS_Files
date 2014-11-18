// PA4 Assignment
// Author: Jacob Rede and Anna Beckman
// Date:   11/14/2014
// Class:  CS200
// Email:  anna_beckman@yahoo.com and jare1987@rams.colostate.edu

public class TermIndexTable implements TermIndex {
	private hashTableNode nodes[];
	private int currentSize;
	private int maxSize;
	
	public TermIndexTable(int startSize) {
		nodes = new hashTableNode[startSize];	//sets the size
		for(int j = 0; j < startSize;j++) {
			this.nodes[j] = new hashTableNode();
		}
		currentSize = 0;
		maxSize = startSize;
	}
	public void insert(Term value, String word) {
		resize();
		int index = hash(word);
		int indexCopy = index;
        int quadraticProb = 0;
        while(quadraticProb < maxSize) {
        	if (this.nodes[index].isDeleted()) {
        		this.nodes[index] = new hashTableNode(value,word,1);
        		currentSize++;
        		return;
        	} 
        	if(this.nodes[index].isEmpty()) {
        		this.nodes[index] = new hashTableNode(value,word,1);
        		currentSize++;
        		return;
        	}
        	quadraticProb++;
        	index = (indexCopy + (quadraticProb * quadraticProb)) % maxSize;
        }
	}
	@Override
	public void add(String filename, String newWord) {
		resize();
		newWord = newWord.toLowerCase();
		Term newTermObject = new Term(newWord);
		newTermObject.incFrequency(filename);
		
		if (contains(newWord)) {
			Term existingTermObject = get(newWord, false);
			existingTermObject.incFrequency(filename);
		} else {
			insert(newTermObject, newWord);
		}
		// TODO Auto-generated method stub
	}
	
	private int hash(String word) {
        return Math.abs(word.hashCode() % maxSize);
    }  
	@Override
	public int size() {
       return currentSize;
    }
	public boolean contains(String key) {
        return get(key, false) !=  null;
    }
	@Override
	public void delete(String word) {
		if (!contains(word)) {
            return;
		}
        int index = hash(word);
        int indexCopy = index;
        int quadraticProb = 0;
        
        while(quadraticProb < maxSize) {
	        if(word.equals(this.nodes[index].getWord())) {//if words match
	        	this.nodes[index].deleteNode();
	        	currentSize--;
	        }
	        quadraticProb++;
    		index = (indexCopy + (quadraticProb * quadraticProb)) % maxSize;
    	}
		
	}
	private void resize() {
		if ( currentSize  >= maxSize * 0.80) {
			rehash();
		}
	}
	
	/**
     * Expand the hash table.
     */
	 private void rehash() {
		 hashTableNode oldNodes[] = new hashTableNode[maxSize];
		 System.arraycopy(this.nodes, 0, oldNodes, 0, oldNodes.length);
		 int oldSize = maxSize;
		 int newSize = (2 * this.maxSize) + 1;
		 this.nodes = new hashTableNode[newSize];
		 this.currentSize = 0;
		 this.maxSize = newSize;
 
		 for(int j = 0; j < maxSize;j++) {
			 this.nodes[j] = new hashTableNode();
		 }
		 for (int index = 0; index < oldSize; index++) {
			 if(oldNodes[index].inTable()) {
				 insert(oldNodes[index].getTerm(), oldNodes[index].getWord());
			 }
		 }
	} // end rehash
	@Override
	public Term get(String word, Boolean printP) {
		int index = hash(word);
		int indexCopy = index;
		int quadraticProb = 0;
	    while(quadraticProb < maxSize && (this.nodes[index].inTable() || this.nodes[index].isDeleted())) {
	        if(word.equals(this.nodes[index].getWord())) {
	        	return this.nodes[index].getTerm();
	        }
	    	quadraticProb++;
	    	index = (indexCopy + (quadraticProb * quadraticProb)) % maxSize;
	    }
	    return null;
	}
    public Term[] getValues() {
    	Term[] allTerms = new Term[maxSize];
    	int counter = 0;
    	for(int j = 0; j < maxSize;j++) {
    		if(this.nodes[j].inTable()) {
    			allTerms[counter] = this.nodes[j].getTerm();
    			counter++;
    		}
    	}
    	return allTerms;
    }
    private class hashTableNode {    
    	private Term termObject;
    	private String word;
    	private int status; //0 = empty, 1 = inTable, 2 = deleted from table
    	public hashTableNode() {
    		this.termObject = null;
    		this.word = null;
    		this.status = 0;
    	}
    	public hashTableNode(Term newTermObject, String newWord, int currentStatus) {
    		this.termObject = newTermObject;
    		this.word = newWord;
    		this.status = currentStatus;
    	}
    	public boolean inTable() {
    		return status==1;
    	}
    	public boolean isDeleted() {
    		return status==2;
    	}
    	public boolean isEmpty() {
    		return status==0;
    	}
    	public void deleteNode() {
    		this.termObject = null;
    		this.word = null;
    		this.status = 2;
    	}
    	public Term getTerm() {
    		return termObject;
    	}
    	public String getWord() {
    		return this.word;
    	}
    	public void print() {
    		if(this.termObject != null && this.word != null) {
    			System.out.println("Term word: "+ termObject.getWord());
        		System.out.println("String word: "+ word);
        		System.out.println("int status(0=empty, 1=intable, 2=deleted): "+ status);
    		} else {
    			System.out.println("Term word: null");
        		System.out.println("String word: null");
        		System.out.println("int status(0=empty, 1=intable, 2=deleted): "+ status);
    		}
    		
    	}
    }
    
}
