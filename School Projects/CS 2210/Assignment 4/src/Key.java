/*
* Name: Raymond Xie
* Student No: 251275727
* Program Name: Key
* Description: The Key Class
 */

public class Key {

    // Instance variables
    private String label;
    private int type;

    // Constructor method:
    public Key(String theLabel, int theType) {
        label = theLabel.toLowerCase();
        type = theType;
    }

    // Getter methods:
    // Returns label variable
    public String getLabel() {
        return label;
    }
    // Returns type variable
    public int getType() {
        return type;
    }

    // Other methods:
    // Compares this key object to k
    public int compareTo(Key k) {
        // Checking if labels and types are the same for both keys
        if(this.getLabel().equals(k.getLabel()) && this.getType() == k.getType()) {
            // Returns 0 if both keys are equal
            return 0;
        // Checking if this key is lexicographically before k or this label = k label and this type < k type
        } else if((compareLex(this.getLabel(), k.getLabel()) < 0) || (this.getLabel().equals(k.getLabel()) && this.getType() < k.getType())) {
            // Returns -1 if this key is smaller than k
            return -1;
        } else {
            // Returns 1 for any other scenario
            return 1;
        }
    }

    // Private helper methods:
    // Compares two strings lexicographically
    private int compareLex(String s1, String s2) {
        // For loop to loop through all characters in strings
        for(int i=0; i<s1.length() && i<s2.length(); i++) {
            // If the two characters at x index in both strings are the same
            if((int) s1.charAt(i) == (int) s2.charAt(i)) {
                // Continues probing the strings
                continue;
            } else {
                // Returns the difference between the two characters at x index
                return (int) s1.charAt(i) - (int) s2.charAt(i);
            }
        }

        // Checks in case two strings are similar (Ex: s1 = apple, s2 = applepie)
        if(s1.length() < s2.length()) {
            // If s1 is shorter than s2, then s1 is lexicographically before than s2 and will return a negative number
            return (s1.length() - s2.length());
        } else if(s1.length() > s2.length()) {
            // If s1 is longer than s2, then s1 is lexicographically after than s2 and will return a positive number
            return (s1.length() - s2.length());
        }

        // If both strings are equal, returns 0
        else {
            return 0;
        }
    }

}
