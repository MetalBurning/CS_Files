import java.util.LinkedList;

/**
 * Stub file for students to fill in. CSU CS200 Fall 2014 Lab 7.
 * @author David Newman (Fall 2010), modified AEH (Fall 2014)
 *
 * @param <E>
 * 
 * @modifiedBy: Jacob Rede
 */
		class InorderIterator {
			
			//TODO: Create your needed instance variables.
			// a queue tracks the order for visiting the tree nodes
			LinkedList inqueue = new LinkedList();
			private TreeNode next;
			/**
			 * Construct a new iterator object.
			 * @param binTree
			 */
			public InorderIterator(TreeNode rootNode) {
				this.next = rootNode;
				//this.depthSearched = 0;
				setInorder();
				
				//TODO: Initialize your instance variables.
			}
			

			/* (non-Javadoc)
			 * Return true if the iterator has more objects yet to return.
			 * @see java.util.Iterator#hasNext()
			 */
			public boolean hasNext() {
				//TODO: Fix this up so it does the right thing.
				if (inqueue.isEmpty()) {
					return false;
				}
				return true;
			}

			/* (non-Javadoc)
			 * Return the first object that has not yet been returned.
			 * @see java.util.Iterator#next()
			 */
			public String next() {
				//TODO: Fix this up so it does the right thing.
				if (inqueue.isEmpty()) {
					return null;
				}
				String tempTerm = new String("tenp");
				tempTerm = (String) inqueue.getFirst();
				inqueue.removeFirst();
				return tempTerm;
			}


			/*
			 * Put the correct order of nodes onto the queue
			 */
			public void setInorder() {
				//TODO: calls inorder
				inorder(this.next);
				
			}
			private void inorder(TreeNode treeNode) {
				//TODO: recursively visit nodes in the tree, 
				//      adding as appropriate to the queue
				if (treeNode != null) {
					inorder(treeNode.getLeft());
					inqueue.add(treeNode.getItem());
					inorder(treeNode.getRight());
				}
			}
		}