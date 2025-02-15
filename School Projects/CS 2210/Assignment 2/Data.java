/*
 * Name: Raymond Xie
 * Student No: 251275727
 * Program: Data
 * Description: Constructor for the Data object, plus two getter commands that return the config and score.
 */

public class Data {

    // Instance variables:
    private String config;
    private int score;

    // Constructor method
    public Data(String config, int score) {
        // Saves config and score in instance variables for later use
        this.config = config;
        this.score = score;
    }

    // Getter methods:
    // Returns the config
    public String getConfig() {
        return this.config;
    }

    // Returns the score
    public int getScore() {
        return this.score;
    }
}
