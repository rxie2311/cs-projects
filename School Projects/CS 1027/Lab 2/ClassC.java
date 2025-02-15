
public class ClassC {

	// Add static to the counter so it is not reset back to 0 every single time a new object is created
	private static int counter = 0;

	public ClassC() {
		counter++;
	}

	public void incCounter() {
		++counter;
	}

	public int getCounter() {
		return counter;
	}

}
