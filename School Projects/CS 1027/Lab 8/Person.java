
public class Person implements Comparable<Person> {
	
	/* Attribute declarations */
	private String name;
	private String city;
	private String email;
			
	/**
	 * Constructor initializes the person's name and email address
	 */
	public Person(String name, String email, String city) {
		this.name = name;
		this.email = email;
		this.city = city;
	}

	public String getName() {
		return name;
	}

	public String getCity() {
		return city;
	}

	public String getEmail() {
		return email;
	}

	private int compareByName(Person other) {

		if(this.name.compareTo(other.getName()) > 0) {
			return 1;
		} else if(this.name.compareTo(other.getName()) < 0) {
			return -1;
		} else {
			return 0;
		}
	}

	private int compareByCity(Person other) {

		if(this.city.compareTo(other.getCity()) > 0) {
			return 1;
		} else if(this.city.compareTo(other.getCity()) < 0) {
			return -1;
		} else {
			return 0;
		}
	}

	private int compareByEmail(Person other) {

		if(this.email.compareTo(other.getEmail()) > 0) {
			return 1;
		} else if(this.email.compareTo(other.getEmail()) < 0) {
			return -1;
		} else {
			return 0;
		}
	}

	/**
	 * toString to display the person's info in a clean format
	 * return String of the person's info
	 */
	public String toString() {
		String s = String.format("%10s\t\t%30s\t\t%10s", name, email, city);
		return s;
	}

	/**
	 * compareTo determines the order of the contacts
	 */
	public int compareTo(Person other) {

		if(ContactList.sortBy == 'n') {
			return compareByName(other);
		} else if(ContactList.sortBy == 'c') {
			return compareByCity(other);
		} else if(ContactList.sortBy == 'e') {
			return compareByEmail(other);
		}

		return 0;
	}

}