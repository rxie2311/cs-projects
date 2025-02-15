public class Player {

    /**
     * This class is the Player class. Player has a total of 3 variables
     * named name, position and jerseyNum that describe the player that is
     * inputted.
     */

    // Private variables
    private String name;
    private String position;
    private int jerseyNum;

    // Constructor
    public Player(String theName, String thePosition, int theJersey) {
        name = theName;
        position = thePosition;
        jerseyNum = theJersey;
    }

    // Getter methods
    public String getName() {
        // Get the player's name
        return name;
    }

    public String getPosition() {
        return position;
    }

    public int getJerseyNum() {
        return jerseyNum;
    }

    // Setter methods
    public void setName(String newName) {
        name = newName;
    }

    public void setPosition(String newPosition) {
        position = newPosition;
    }

    public void setJerseyNum(int newJersey) {
        jerseyNum = newJersey;
    }

}
