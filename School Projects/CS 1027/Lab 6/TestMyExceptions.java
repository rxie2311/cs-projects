
public class TestMyExceptions {
	
	public static void m1 (int t) {
		System.out.println("Top of m1");
		try {
			if (t > 10)
				throw new MyCheckedException("t is large");
		} catch (MyCheckedException e) {
			System.out.println("Error caught");
		}
		System.out.println("Bottom of m1");
	}
	
	public static void m2 (int t) {
		System.out.println("Top of m2");
		if (t > 10)
			throw new MyUncheckedException("t is large");
		System.out.println("Bottom of m2");
	}

	public static void main(String[] args) {
		
		m1(15);
		m2(15);
		

	}

}
