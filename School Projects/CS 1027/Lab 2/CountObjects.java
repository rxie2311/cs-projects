
public class CountObjects {

	public static void main(String[] args) {

		int numObjects;
		ClassC c = null;
		for (int i = 0; i < RandomNumber.getRandomNumber(10, 20); ++i) {
			c = new ClassC();
		}
		numObjects = c.getCounter();
		System.out.println("Number of objects created is " + numObjects);
	}

}
