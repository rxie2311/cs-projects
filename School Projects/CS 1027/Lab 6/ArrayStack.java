
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

	public void push(T element) {
		T temp = null;
		T temp2;

		for(int i=0; i<array.length; i++) {
			if(i == 0) {
				temp = array[i];
				array[i] = element;
			} else {
				temp2 = array[i];
				array[i] = temp;
				temp = temp2;
			}
		}
	}

	public T pop() {
		if(array[top] == null) {
			return null;
		}

		T temp = array[top];
		T temp2, temp3;

		for(int i=0; i<array.length; i++) {
			if(i == array.length-1) {
				array[i] = null;
			} else {
				array[i] = array[i+1];
			}

		}

		return temp;
	}


	public T peek() {
		if (isEmpty()) throw new EmptyCollectionException("Empty stack");
		return array[top];
	}


	public int size() {
		int count = 0;
		while(array[count] != null) {
			count++;
		}

		return count;
	}


	public boolean isEmpty() {
		if(array.length == 0) {
			return true;
		}

		int nullCount = 0;
		for(int i=0; i< array.length; i++) {
			if(array[i] == null) {
				nullCount++;
			}
		}

		if(nullCount == array.length) {
			return true;
		} else {
			return false;
		}
	}


	public String toString() {
		String s = "Stack: ";
		int count = 0;

		while (array[count] != null) {
			s += array[count] + " ";
			count++;
		}
		return s;
	}

}
