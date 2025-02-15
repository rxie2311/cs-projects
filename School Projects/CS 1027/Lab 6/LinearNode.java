
public class LinearNode<T> {
	
	private T element;
	private LinearNode<T> next;
	
	public LinearNode (T element) {
		this.element = element;
		next = null;
	}
	
	public LinearNode () {
		element = null;
		next = null;
	}
	
	public T getElement () {
		return element;
	}
	
	public LinearNode<T> getNext() {
		return next;
	}
	
	public void setElement (T element) {
		this.element = element;
	}
	public void setNext (LinearNode<T> next) {
		this.next = next;
	}

}
