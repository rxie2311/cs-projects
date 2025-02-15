
public class TestStack {
	
	public static void performStackActions (StackADT<String> stack) {
		
		// Test 1 - empty stack
		System.out.print("Test 1\t");
		try {
			if (stack.isEmpty() && stack.size() == 0) System.out.println("passed");
			else System.out.println("failed");
		} catch (Exception e) { System.out.println("failed"); }
		
		stack.push("first");
		stack.push("second");
		stack.push("third");
		
		// Test 2 - push
		System.out.print("Test 2\t");
		try {
			if (!stack.isEmpty() && stack.size() == 3) System.out.println("passed");
			else System.out.println("failed");
		} catch (Exception e) { System.out.println("failed"); }
		
		
		// Test 3 - toString
		System.out.print("Test 3\t");
		try {
			if (stack.toString().equals("Stack: third second first ")) System.out.println("passed");
			else System.out.println("failed");
		} catch (Exception e) { System.out.println("failed"); }
		
		
		// Test 4 - peek
		System.out.print("Test 4\t");
		try {
			String res = stack.peek();
			if (res.equals("third") && stack.size() == 3) System.out.println("passed");
			else System.out.println("failed");
		} catch (Exception e) { System.out.println("failed"); }
		
		
		// Test 5 - pop
		System.out.print("Test 5\t");
		try {
			String res1 = stack.pop();
			String res2 = stack.pop();
			String res3 = stack.pop();
			if (res1.equals("third") && res2.equals("second") && res3.equals("first") && stack.isEmpty()) System.out.println("passed");
			else System.out.println("failed");
		} catch (Exception e) { System.out.println("failed"); }

	}
	
	public static void main (String[] args) {
		StackADT<String> S1 = new ArrayStack<String>();
		StackADT<String> S2 = new LinkedStack<String>();

		System.out.println("Testing ArrayStack:");
		performStackActions(S1);
		System.out.println("Testing LinkedStack:");
		performStackActions(S2);

	}

}
