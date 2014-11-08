//PA3 Assignment
//Author: Alex Eibner and Jacob Rede
//Date:   9/17/2014
//Class:  CS200
//Email:  alexeibner@gmail.com	and jare1987@rams.colostate.edu

/*
 * Two methods (mergesort, merge) taken from the text:
 * Data Abstraction & Problem Solving with Java 3rd Edition
 * by: Janet J. Prichardd and Frank M. Carrano
 */

import java.util.ArrayList;

public class Mergesort {
	
  private int[] numbers;
  private int[] helper;
  private int counter;
  private int listLength;
  private int mainSortSelection;
  private ArrayList<Term> termIndex;
  private ArrayList<Term> termHelper;
  
/*
 * This is not constructor.
 * We need to return the sorted arraylist (termIndex).
 * But functions like a constructor.
 */
  
  public ArrayList<Term> Mergesort(ArrayList<Term> values, int selectionToCompare) {
	  
    listLength = values.size();
    this.termIndex = new ArrayList<Term>(values);
    this.termHelper = new ArrayList<Term>(values);
    this.mainSortSelection = selectionToCompare;//1 = words, 0 = integers
    this.counter = 0;
    mergesort(0, listLength-1);
    return termIndex;
    
  }
  
  /*
   * Used this method for testing.
   */
  
//  public void print() {
//	  for(int j =0;j< listLength;j++) {
//		  if (mainSortSelection == 1) {
//			  System.out.println("word Location: "+j+" value: "+termIndex.get(j).getTotalFrequency()+" word: "+termIndex.get(j).getWord());
//		  } else {
//			  System.out.println("Location: "+j+" value: "+termIndex.get(j).getTotalFrequency()+" word: "+termIndex.get(j).getWord());
//		  }
//	  }
//  }
  
  private void mergesort(int first, int last) {
	  
    // Check if low is smaller than high, if not, then the array is sorted.  
    if (first < last) {
    	
      // Gets the index of the element which is in the middle of the array.
      int mid = (first + last) / 2;
     
      // Sorts the left side of the array.
      mergesort(first, mid);
      
      // Sorts the right side of the array.
      mergesort(mid+1, last);
     
      // Combines them both.
      merge(first, mid, last);
      
    }
    
  }

  private void merge(int first, int mid, int last) {
	  
	  int first1 = first;
	  int last1 = mid;
	  int first2 = mid+1;
	  int last2 = last; 
	  int index = first1;
	  
	  while((first1 <= last1) && (first2 <= last2)) {
		  
		  if(termIndex.get(first1).compareTo(termIndex.get(first2), mainSortSelection) <= 0) {
			  
			  termHelper.set(index, termIndex.get(first1));
			  first1++;
			  this.counter++;
			  
		  } else {
			  
			  termHelper.set(index, termIndex.get(first2));
			  first2++;
			  
		  }
		  
		  index++;
		  
	  }
	   
	  while(first1 <= last1) {
		  
		  termHelper.set(index, termIndex.get(first1));
		  first1++;
		  index++;
		  
	  }
	  
	  while(first2 <= last2) {
		  
		  termHelper.set(index, termIndex.get(first2));
		  first2++;
		  index++;
		  
	  }
	  
	  for(index = first; index <= last; ++index) {
		  
		  termIndex.set(index, termHelper.get(index));
		  
	  }
	  
  }
  
  public int getCounter() {
	  
	  return this.counter;
	  
  }
  
} 