
public class TestReverse {
	
	
	public static void main (String[] args) {

		String[] arr1 = new String[] {"ewok", "droid", "yoda", "lightsaber", "jedi"};
		ReversibleArray<String> revArr1 = new ReversibleArray<String>(arr1);
		System.out.println(revArr1.toString());
		revArr1.reverse();
		System.out.println(revArr1.toString());
		
		Integer[] arr2 = new Integer[] {11, 22, 33, 44, 55, 66, 77};
		ReversibleArray<Integer> revArr2 = new ReversibleArray<Integer>(arr2);
		System.out.println(revArr2.toString());
		revArr2.reverse();
		System.out.println(revArr2.toString());

		Person p1 = new Person("Terry", "Duktul");
		Person p2 = new Person("Phil", "Harmonic");
		Person p3 = new Person("Matt", "Tress");
		Person p4 = new Person("Burt", "Toaste");
		Person p5 = new Person("Elle", "Faunt");
		Person[] arr3 = new Person[] {p1, p2, p3, p4, p5};
		ReversibleArray<Person> revArr3 = new ReversibleArray<Person>(arr3);
		System.out.println(revArr3.toString());
		revArr3.reverse();
		System.out.println(revArr3.toString());
		
	}

}
