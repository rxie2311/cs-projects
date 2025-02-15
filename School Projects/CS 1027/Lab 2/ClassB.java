
public class ClassB {

	private int counter = 0;

	public ClassB() {
		counter = 1;
	}

	public void incCounter() {
		++counter;
	}

	public int getCounter() {
		return counter;
	}

	public static void main(String[] args) {
		int i;

		// Create a new object to utilize the non-static variables
		ClassB newVar = new ClassB();

		i = newVar.counter;
		newVar.incCounter();
		System.out.println("i = " + i + " counter = " + newVar.counter);
	}

}
