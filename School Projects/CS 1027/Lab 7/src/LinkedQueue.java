/**
 * LinkedQueue represents a linked implementation of a queue.
 * 
 * @author Dr. Lewis
 * @author Dr. Chase
 * @version 1.0, 08/12/08
 */

public class LinkedQueue<T> implements QueueADT<T>
{
	private int count;
	private LinearNode<T> front, rear;

	/**
	 * Creates an empty queue.
	 */
	public LinkedQueue() {
		count = 0;
		front = rear = null;
	}

	/**
	 * Adds the specified element to the rear of this queue.
	 *
	 * @param element  the element to be added to the rear of this queue
	 */
	public void enqueue (T element) {
		LinearNode<T> curr = new LinearNode<>(element);

		if(front == null) {
			front = curr;
			count++;
		} else {
			rear.setNext(curr);
		}
		rear = curr;
	}


	public T dequeue() throws EmptyCollectionException {
		if(isEmpty()) {
			rear = null;
			throw new EmptyCollectionException("Empty queue");
		} else {
			LinearNode<T> curr = front;
			front = front.getNext();
			count--;
			return curr.getElement();
		}
	}


	public T first() throws EmptyCollectionException {
		if(front == null) {
			throw new EmptyCollectionException("Empty queue");
		}

		return front.getElement();
	}

	/**
	 * Returns true if this queue is empty and false otherwise. 
	 *
	 * @return  true if this queue is empty and false if otherwise
	 */
	public boolean isEmpty() {
		if(front == null) {
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Returns the number of elements currently in this queue.
	 *
	 * @return  the integer representation of the size of this queue
	 */
	public int size() {
		LinearNode<T> curr = front;
		int counter = 0;

		while(curr != null) {
			counter++;
			curr = curr.getNext();
		}

		return counter;
	}

	public String toString() {
		LinearNode<T> curr = front;
		String S = "";

		while(curr != null) {
			S = S + curr.getElement() + " ";
			curr = curr.getNext();
		}

		return S;

	}


}
