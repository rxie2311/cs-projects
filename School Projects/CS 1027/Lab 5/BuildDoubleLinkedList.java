
public class BuildDoubleLinkedList {
	
	private DoubleLinkedNode<Character> front, rear;
	private static char[] letters = new char[] {'K', 'T', 'E', 'N', 'P', 'A', 'L'};

	public BuildDoubleLinkedList () {
		build();
	}

	public void remove (Character elem) {
		// Setting the current node to the front of the list
		DoubleLinkedNode<Character> curr = front;

		// Using a for loop to loop through all elements of the list (7)
		for(int i=0; i < 7; i++) {
			// Checks if current is null, if it is, returns
			if(curr == null) {
				return;
			}

			// If current reaches the specified element
			if(curr.getElement().equals(elem)) {
				// Removing a front node
				if(front.getElement() == elem) {
					front = curr.getNext();
					curr = curr.getNext();
					curr.setPrevious(null);
					return;
				// Removing a rear node
				} else if(rear.getElement() == elem) {
					rear = curr.getPrevious();
					curr = curr.getPrevious();
					curr.setNext(null);
					return;
				// Removing an internal node
				} else {
					curr.getPrevious().setNext(curr.getNext());
					curr.getNext().setPrevious(curr.getPrevious());

				}
			}

			// Moves current to the next node in the list
			curr = curr.getNext();

		}
	}

	private void build () {
		DoubleLinkedNode<Character> pnode, node;
		
		node = new DoubleLinkedNode<Character>(letters[0]);
		pnode = front = node;
		for (int i = 1; i < 7; i++) {
			node = new DoubleLinkedNode<Character>(letters[i]);
			pnode.setNext(node);
			node.setPrevious(pnode);
			pnode = node;
		}
		rear = node;
	}
	
	public DoubleLinkedNode<Character> getFront () {
		return front;
	}
	
	public DoubleLinkedNode<Character> getRear () {
		return rear;
	}
	
	public void printF (DoubleLinkedNode<Character> node) {
		System.out.print("Forward:  ");
		DoubleLinkedNode<Character> curr = front;
		while (curr != null) {
			System.out.print(curr.getElement() + " ");
			curr = curr.getNext();
		}
		System.out.print("\n");
	}
	
	public void printR (DoubleLinkedNode<Character> node) {
		System.out.print("Reverse:  ");
		DoubleLinkedNode<Character> curr = rear;
		while (curr != null) {
			System.out.print(curr.getElement() + " ");
			curr = curr.getPrevious();
		}
		System.out.print("\n");
	}
	
	
	
	public static void main (String[] args) {
		BuildDoubleLinkedList dll = new BuildDoubleLinkedList();

		System.out.println("Original List:");
		dll.printF(dll.getFront());
		dll.printR(dll.getRear());
		System.out.println("***");
		
		System.out.println("Removing an internal node:");
		dll.remove('N');
		dll.printF(dll.getFront());
		dll.printR(dll.getRear());
		System.out.println("***");
		
		System.out.println("Removing the front node:");
		dll.remove('K');
		dll.printF(dll.getFront());
		dll.printR(dll.getRear());
		System.out.println("***");
		
		System.out.println("Removing the rear node:");
		dll.remove('L');
		dll.printF(dll.getFront());
		dll.printR(dll.getRear());
		System.out.println("***");
		
		System.out.println("Trying to remove a non-existent node:");
		dll.remove('X');
		dll.printF(dll.getFront());
		dll.printR(dll.getRear());
		System.out.println("***");
	}

}
