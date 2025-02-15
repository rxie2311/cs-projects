
public class Card implements Comparable<Card> {
	
	private String suit; // S (spade), H (heart), D (diamond), or C (club)
	private String rank; // A (ace), 2, 3, ..., 10, J (jack), Q (queen), or K (king)

	public Card (String suit, String rank) {
		this.suit = suit;
		this.rank = rank;
	}

	public String getSuit () {
		return suit;
	}
	
	public String getRank () {
		return rank;
	}
	
	public void setSuit (String suit) {
		this.suit = suit;
	}
	
	public void setRank (String rank) {
		this.rank = rank;
	}

	private int getSuitValue() {

		if(getSuit().equals("D")) {return 1;}

		else if(getSuit().equals("C")) {return 2;}

		else if(getSuit().equals("H")) {return 3;}

		else {return 4;}

	}

	private int getRankValue() {

		if(getRank().equals("J") || getRank().equals("Q") || getRank().equals("K")) {return 11;}

		else if(getRank().equals("A")) {return 12;}

		else {return Integer.parseInt(rank);}
	}

	public boolean equals(Card other) {

		if(this.rank.equals(other.getRank()) && this.suit.equals(other.getSuit())) {return true;}

		else {return false;}

	}

	public int compareTo(Card other) {
		if(equals(other)) {
			return 0;
		}

		if(this.getRankValue() > other.getRankValue()) {
			return 1;
		} else if(this.getRankValue() < other.getRankValue()) {
			return -1;
		}

		if(this.getSuitValue() > other.getSuitValue()) {
			return 1;
		} else {
			return -1;
		}
	}

	public String toString () {
		return rank + " of " + suit;
	}

}
