public class ClassA {
	private final int SIZE_ARRAY = 5;
	public int numItems;
	public int[] arrItems;

	public ClassA(int n, int[] arr) {
		numItems = n;
		arrItems = arr;
	}

	public ClassA() {
		numItems = 0;
		arrItems = new int[SIZE_ARRAY];
	}

	int trueCount = 0;

	public boolean equals(ClassA otherObject) {
		if(this.numItems == otherObject.numItems) {
			for(int i=0; i<this.arrItems.length; i++) {
				if(this.arrItems[i] == otherObject.arrItems[i]) {
					trueCount++;
				}
			}
			if(trueCount == this.arrItems.length) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}
}
