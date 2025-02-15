
public class ArrayStack<T> implements StackADT<T> {
	
	private T[] array;
	private int top;
	private final int DEFAULT_CAPACITY = 5;
	
	public ArrayStack () {
		array = (T[])(new Object[DEFAULT_CAPACITY]);
		top = 0;
	}
	
	public ArrayStack (int initialCapacity) {
		array = (T[])(new Object[initialCapacity]);
		top = 0;
	}
	
	public void push (T element) {
		if (top == array.length) expandCapacity();
		array[top] = element;
		top++;
	}
	
	public T pop() {
		if (isEmpty()) throw new EmptyCollectionException("Empty stack");
		top--;
		T result = array[top];
		array[top] = null;
		return result;
	}
	
	public T peek() {
		if (isEmpty()) throw new EmptyCollectionException("Empty stack");
		
		return array[top-1];
	}
	
	public int size() {
		return top;
	}
	
	public boolean isEmpty() {
		return top == 0;
	}
	
	public String toString() {
		String s = "Stack: ";
		
		for (int i = top-1; i >= 0; i--)
			s += array[i] + " ";
		
		return s;
	}
	
	
	private void expandCapacity() {
		T[] larger = (T[])(new Object[array.length+5]);
		
		for (int i = 0; i < array.length; i++) {
			larger[i] = array[i];
		}
		array = larger;
	}

}
