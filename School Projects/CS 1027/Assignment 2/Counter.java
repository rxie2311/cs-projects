public class Counter {

    // Instance variables
    PowerSet<Card> cardps;
    Card starter;

    // Constructor method
    public Counter(Card[] hand, Card starter) {
        // Initializing starter
        this.starter = starter;
        // Generating power set using hand
        cardps = new PowerSet(hand);
    }

    // Counting points
    public int countPoints() {
        // Variable to store total amount of points
        int total = 0;
        // Calculation using private helper methods
        total = total + pairs() + run() + fifteen() + flush() + hisKnobs();

        // Returns the total score
        return total;
    }

    // If there are pairs
    private int pairs() {
        // Counter to store the number of points
        int totalPoints = 0;

        // Loops through the length of the power set
        for(int i=0; i<cardps.getLength(); i++) {
            // If it finds a subset within with length of 2
            if(cardps.getSet(i).getLength() == 2) {
                // Checks for a pair
                if(cardps.getSet(i).getElement(0).getLabel().equals(cardps.getSet(i).getElement(1).getLabel())) {
                    // Adds 2 points
                    totalPoints = totalPoints + 2;
                }
            }
        }

        // Returns the total points from pairs
        return totalPoints;
    }

    // If cards add up to 15
    private int fifteen() {
        // Counter to store total points
        int totalPoints = 0;

        // Loops through the length of the power set
        for(int i=0; i<cardps.getLength(); i++) {
            // Stores the total sum of the cards
            int totalmark = 0;

            // Loops through each subset of the power set
            for(int j=0; j<cardps.getSet(i).getLength(); j++) {
                // Adds up the totals of the cards using getFifteenRank
                totalmark = totalmark + cardps.getSet(i).getElement(j).getFifteenRank();
            }
            // If the total amount is equal to 15:
            if (totalmark == 15) {
                // Adds 2 points
                totalPoints = totalPoints + 2;
            }
        }

        // Returns the total points
        return totalPoints;
    }

    // Checking for runs
    private int run() {
        // Variables to store longest run and amount of runs
        int longest = 0;
        int count = 0;

        // Loops through the length of the power set
        for(int i=0; i<cardps.getLength(); i++) {
            // Checks if the length of each power set is longer than the longest one
            if(cardps.getSet(i).getLength() > longest) {
                // If isRun returns true
                if(isRun(cardps.getSet(i)) == true) {
                    // Adds 1 to count and updates longest
                    longest = cardps.getSet(i).getLength();
                    count = 1;
                }
            // If the length of the power set is the same as longest
            } else if(cardps.getSet(i).getLength() == longest) {
                // If isRun returns true
                if(isRun(cardps.getSet(i)) == true) {
                    // Adds 1 to count
                    count++;
                }
            }
        }

        // Multiplies longest and count to get total points and returns it
        return longest*count;
    }

    // Checking for flush
    private int flush() {

        // Loops through the length of the power set
        for(int i=0; i<cardps.getLength(); i++) {
            // If it finds a subset within with length of 4
            if(cardps.getSet(i).getLength() == 4) {
                // Checking if all suits are equal
                if(cardps.getSet(i).getElement(0).getSuit().equals(cardps.getSet(i).getElement(1).getSuit()) &&
                        cardps.getSet(i).getElement(1).getSuit().equals(cardps.getSet(i).getElement(2).getSuit()) &&
                        cardps.getSet(i).getElement(2).getSuit().equals(cardps.getSet(i).getElement(3).getSuit())) {
                    // Checking if starter suit is equal to the rest of the suits
                    if(starter.getSuit().equals(cardps.getSet(i).getElement(0).getSuit())) {
                        // If equal: returns 5
                        return 5;
                    } else {
                        // If unequal: returns 4
                        return 4;
                    }
                }
            }
        }

        // Returns 0 if there are no flushes
        return 0;
    }

    // Checking for his knobs
    private int hisKnobs() {

        // Loops through the length of the power set
        for(int i=0; i<cardps.getLength(); i++) {
            // If it finds a subset within with length of 4
            if(cardps.getSet(i).getLength() == 4) {
                // Loops through length of the subset
                for(int j=0; j<4; j++) {
                    // If it finds a JACK
                    if(cardps.getSet(i).getElement(j).getLabel().equals("J")) {
                        // If the JACK suit is equal to the starter suit
                        if(cardps.getSet(i).getElement(j).getSuit().equals(starter.getSuit())) {
                            // Returns 1 if true
                            return 1;
                        } else {
                            // Returns 0 if false
                            return 0;
                        }
                    }
                }
            }
        }

        // Returns 0 if no JACKS are found
        return 0;
    }

    // Provided isRun method
    private boolean isRun (Set<Card> set) {
        // In this method, we are going through the given set to check if it constitutes a run of 3 or more
        // consecutive cards. To do this, we are going to create an array of 13 cells to represent the
        // range of card ranks from 1 to 13. We go through each card and increment the cell corresponding to
        // each card's rank. For example, an Ace (rank 1) would cause the first (index 0) cell to increment.
        // An 8 would cause the 8th (index 7) cell to increment. When this loop is done, the array will
        // contain 5 or less cells with values of 1 or more to represent the number of cards with each rank.
        // Then we can use this array to search for 3 or more consecutive non-zero values to represent a run.

        int n = set.getLength();

        if (n <= 2) return false; // Run must be at least 3 in length.

        int[] rankArr = new int[13];
        for (int i = 0; i < 13; i++) rankArr[i] = 0; // Ensure the default values are all 0.

        for (int i = 0; i < n; i++) {
            rankArr[set.getElement(i).getRunRank()-1] += 1;
        }

        // Now search in the array for a sequence of n consecutive 1's.
        int streak = 0;
        int maxStreak = 0;
        for (int i = 0; i < 13; i++) {
            if (rankArr[i] == 1) {
                streak++;
                if (streak > maxStreak) maxStreak = streak;
            } else {
                streak = 0;
            }
        }
        if (maxStreak == n) { // Check if this is the maximum streak.
            return true;
        } else {
            return false;
        }

    }

}
