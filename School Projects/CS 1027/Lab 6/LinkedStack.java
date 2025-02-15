
public class LinkedStack<T> implements StackADT<T> {

	private LinearNode<T> top;
	
	public void push(T element) {
		LinearNode<T> newNode = new LinearNode<T>(element);
		newNode.setNext(top);
		top = newNode;
	}

	public T pop() {
		if(top == null) {
			return null;
		}

		T temp = top.getElement();
		top = top.getNext();

		return temp;
	}
	

	public T peek() {
		if (isEmpty()) throw new EmptyCollectionException("Empty stack");
		return top.getElement();
	}


	public int size() {
		LinearNode<T> curr = top;
		int count = 0;

		while(curr != null) {
			count++;
			curr = curr.getNext();
		}

		return count;
	}
	

	public boolean isEmpty() {

		if(top == null) {
			return true;
		} else {
			return false;
		}
	}
	
	
	public String toString () {
		String s = "Stack: ";
		LinearNode<T> curr = top;
		while (curr != null) {
			s += curr.getElement() + " ";
			curr = curr.getNext();
		}
		return s;
	}

}
