
public class Snail {
	
	public static char icon = '@';
	private int position;
	private QueueADT<Integer> movePattern = new LinkedQueue<>();

	public Snail (int[] pattern) {
		position = 0;

		for(int i=0; i<pattern.length; i++) {
			movePattern.enqueue(pattern[i]);
		}
	}
	
	public void move () {
		int step;
		int raceLen = SnailRace.raceLength;

		step = movePattern.dequeue();
		movePattern.enqueue(step);
		position+= step;
		if(raceLen < position) {
			position = raceLen;
		}
	}
	
	public int getPosition () {
		return position;
	}
	
	public void display () {
		int dashesBefore = position;
		int dashesAfter = SnailRace.raceLength - position;

		for(int i=0; i<dashesBefore; i++) {
			System.out.print("-");
		}
		System.out.print(icon);
		for(int i=dashesAfter; i>0; i--) {
			System.out.print("-");
		}
		System.out.print("\n");
	}

}
