/*
 * Name: Raymond Xie
 * Student No: 251275727
 * Program Name: Record
 * Description: The Record Class
 */

public class Record {

    // Instance variables
    private Key theKey;
    private String data;

    // Constructor method:
    public Record(Key k, String theData) {
        theKey = k;
        data = theData;
    }

    // Getter methods:
    // Returns theKey
    public Key getKey() {
        return theKey;
    }
    // Returns data
    public String getDataItem() {
        return data;
    }

}
