// Importing Java Linked List class as per assignment instructions (allowed for use)
import java.util.LinkedList;

/*
* Name: Raymond Xie
* Student No: 251275727
* Program: Hash Dictionary
* Description: Various commands that create a hash dictionary, removes Data objects from the dictionary,
* gets score values based on their configs, and returns the amount of items in the hash dictionary.
*/

public class HashDictionary implements DictionaryADT {

    // Instance variables:
    // Linked list to be stored in dict
    private LinkedList<Data> bucket;
    // Hash dictionary called dict that stores linked lists
    private LinkedList<Data> dict[];
    // Size of the hash dictionary
    private int size;

    // Constructor method
    public HashDictionary(int size) {
        // Creates new hash dictionary (array) of type LinkedList with a size of size
        dict = new LinkedList[size];
        // Saves size as an instance variable
        this.size = size;
    }


    // Private methods:
    // Creates a hash code for each Data object that will be added to the hash dictionary
    private static int hash(String key) {
        // Initial value of hash key
        int hashKeyVal = 0;

        // For loop to calculate hash key value
        for(int i=0; i<key.length(); i++) {
            // Puts the integer value of current character of the string into charCode
            int charCode = key.charAt(i) - 96;
            // Formula for Polynomial Hashing: h(k) = s0 + (s1*x) + (s2*x^2) + ... + (s(n-1) * x^(n-1)) % size
            // x = any random integer (27 in this case)
            hashKeyVal = (hashKeyVal * 27) + charCode;
        }
        // Returns the hash code
        return hashKeyVal;
    }

    // Changes the raw hash into a smaller/positive number to fit into the hash dictionary
    private int compression(int hashKeyVal) {
        // Returns absolute value of hashKeyVal (since it could be negative) % size to get the index of the Data object
        return Math.abs(hashKeyVal) % size;
    }

    // Checks if there is a duplicate key in the hash dictionary
    private boolean isDupe(Data record) {
        // Storing the key (config) of record into variable
        String key = record.getConfig();
        // Creating hash key of config in record
        int hashKey = compression(hash(key));

        // Checks the index where the key would be stored in the dictionary
        if(dict[hashKey] == null) {
            // If there is nothing there, then the duplicate does not exist
            return false;
        } else {
            // Loops through the linked list at index hashKey
            for(int i=0; i<dict[hashKey].size(); i++) {
                // If duplicate is found, returns true
                if(dict[hashKey].get(i).getConfig().equals(key)) {
                    return true;
                }
            }
        }
        // If true is not returned, automatically assumes no duplicate and returns false
        return false;
    }


    // Implemented methods:
    // Stores a Data object into the dictionary
    public int put(Data record) throws DictionaryException {
        // Storing the key (config) of record into variable
        String key = record.getConfig();
        // Creating hash key of config in record
        int hashKey = compression(hash(key));

        // If there is nothing at index hashKey, creates new linked list
        if(dict[hashKey] == null) {
            // Creates new linked list at location
            bucket = new LinkedList<Data>();
            dict[hashKey] = bucket;
            // Adds record into the linked list at index hashKey
            bucket.add(record);

        // If linked list already exists at the location
        } else {
            // Checks for duplicates and throws an exception if one is found
            if(isDupe(record)) {
                throw new DictionaryException();

            // If no dupes are found, uses separation chaining to add record into the linked list at index hashKey
            } else if(!isDupe(record)) {
                dict[hashKey].add(record);
            }
        }
        // Returns 0 at the end
        return 0;
    }

    // Removes a Data object from the dictionary
    public void remove(String config) throws DictionaryException {
        // Turning config into a hash key to locate index in hash dictionary
        int hashKey = compression(hash(config));

        // Checks if the index even exists
        if(dict[hashKey] == null) {
            // Throws error if hashKey index doesn't exist
            throw new DictionaryException();
        }

        // Counter variable
        int i=0;
        // While loop to loop through the linked list stored in index hash key of dict
        while(i < dict[hashKey].size()) {
            // If config equals to the key in the linked list
            if(dict[hashKey].get(i).getConfig().equals(config)) {
                // Removes record from index i in dict[hashKey]
                dict[hashKey].remove(i);
                // Breaks out and returns
                return;
            }
            // Adds 1 to the counter to continue the while loop
            i++;
        }

        // If the key is not found in the dictionary, throws an error
        throw new DictionaryException();
    }

    // Returns the score stored in the dictionary using the key (config)
    public int get(String config) {
        // Turning config into a hash key to locate index in hash dictionary
        int hashKey = compression(hash(config));

        // Checks if the index even exists
        if(dict[hashKey] == null) {
            // Returns -1 if hashKey index doesn't exist
            return -1;
        }

        // Counter variable
        int i=0;
        // While loop to loop through the linked list stored in index hash key of dict
        while(i < dict[hashKey].size()) {
            // If config equals to the key in the linked list
            if(dict[hashKey].get(i).getConfig().equals(config)) {
                return dict[hashKey].get(i).getScore();
            }
            // Adds 1 to the counter to continue the while loop
            i++;
        }

        // Returns -1 if key is not found
        return -1;
    }

    // Returns the amount of Data objects in the dictionary
    public int numRecords() {
        // Counter variable
        int items = 0;

        // For loop to cycle through the dictionary
        for(int i=0; i<dict.length; i++) {
            // Only enters the second for loop if index i is not null
            if(dict[i] != null) {
                // For loop to cycle through the linked list in index i
                for(int j=0; j<dict[i].size(); j++) {
                    if(dict[i].get(j) != null) {
                        // Adds 1 to items if index j is not null
                        items++;
                    }
                }
            }
        }
        // Returns items
        return items;
    }
}