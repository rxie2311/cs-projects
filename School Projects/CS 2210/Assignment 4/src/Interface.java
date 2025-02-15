import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/*
 * Name: Raymond Xie
 * Student No: 251275727
 * Program Name: Interface
 * Description: Implements the user interface
 */

public class Interface {

    // Main method:
    public static void main(String[] args) {
        // New ordered dictionary
        BSTDictionary dict = new BSTDictionary();

        // Try-catch for file reading:
        try {
            // Variables to store file and new scanner to read file
            File f = new File(args[0]);
            Scanner scan = new Scanner(f);

            // While loop to loop through the file until file runs out of lines
            while(scan.hasNextLine()) {
                // Scanning string and label
                String label = scan.nextLine();
                String data = scan.nextLine();

                // Case 1: line 2 starts with '/' (french translation)
                if(data.startsWith("/")) {
                    // Creates new key and record variables
                    Key k = new Key(label, 2);
                    Record rec = new Record(k, data.replace("/", ""));
                    // Inserting record into dictionary
                    dict.put(rec);

                // Case 2: line 2 starts with '-' (sound)
                } else if(data.startsWith("-")) {
                    // Creates new key and record variables
                    Key k = new Key(label, 3);
                    Record rec = new Record(k, data.replace("-", ""));
                    // Inserting record into dictionary
                    dict.put(rec);

                // Case 3: line 2 starts with '+' (music)
                } else if(data.startsWith("+")) {
                    // Creates new key and record variables
                    Key k = new Key(label, 4);
                    Record rec = new Record(k, data.replace("+", ""));
                    // Inserting record into dictionary
                    dict.put(rec);

                // Case 4: line 2 starts with '*' (voice)
                } else if(data.startsWith("*")) {
                    // Creates new key and record variables
                    Key k = new Key(label, 5);
                    Record rec = new Record(k, data.replace("*", ""));
                    // Inserting record into dictionary
                    dict.put(rec);

                // Case 5: line 2 ends with 'jpg' (image)
                } else if(data.endsWith("jpg")) {
                    // Creates new key and record variables
                    Key k = new Key(label, 6);
                    Record rec = new Record(k, data);
                    // Inserting record into dictionary
                    dict.put(rec);

                // Case 6: line 2 ends with 'gif' (animated image)
                } else if(data.endsWith("gif")) {
                    // Creates new key and record variables
                    Key k = new Key(label, 7);
                    Record rec = new Record(k, data);
                    // Inserting record into dictionary
                    dict.put(rec);

                // Case 7: line 2 ends with 'html' (website)
                } else if(data.endsWith("html")) {
                    // Creates new key and record variables
                    Key k = new Key(label, 8);
                    Record rec = new Record(k, data);
                    // Inserting record into dictionary
                    dict.put(rec);

                // Case 8: line 2 does not start or end with any symbol (definition)
                } else {
                    // Creates new key and record variables
                    Key k = new Key(label, 1);
                    Record rec = new Record(k, data);
                    // Inserting record into dictionary
                    dict.put(rec);
                }
            }

        // If the file could not be found, tells the user the error
        } catch (FileNotFoundException e) {
            System.out.println("Error: Could not find specified file.");

        // If the key is already in the dictionary
        } catch (DictionaryException e) {
            System.out.println("Error: Tree already stores a record with the same key.");
        }

        // Variable to check if the user has exited or not
        boolean exit = false;

        // While loop to loop through the user's commands
        while(!exit) {
            // User input
            StringReader keyboard = new StringReader();
            String line = keyboard.read("Enter next command: ");
            // Turns line into lower case to avoid case based errors
            line = line.toLowerCase();

            // Exit: Terminates the program
            if(line.equals("exit")) {
                // Sets exit variable to true so the next loop exits out of the while loop
                exit = true;

            // Define: Outputs the definition of the key entered (type 1)
            } else if(line.startsWith("define")) {
                // Splits the string to take out the label
                String[] splitLine = line.split("\\s+");
                // Creates a new key to search for in the dictionary
                Key k = new Key(splitLine[1], 1);
                Record result = dict.get(k);
                // Checks if the label exists in the dictionary
                if(result != null) {
                    // Prints out the data item
                    System.out.println(result.getDataItem());
                } else {
                    // Prints out error message
                    System.out.println("The word " + splitLine[1] + " is not in the ordered dictionary");
                }

            // Translate: Outputs the translation of the key entered in French (type 2)
            } else if(line.startsWith("translate")) {
                // Splits the string to take out the label
                String[] splitLine = line.split("\\s+");
                // Creates a new key to search for in the dictionary
                Key k = new Key(splitLine[1], 2);
                Record result = dict.get(k);
                // Checks if the label exists in the dictionary
                if(result != null) {
                    // Prints out the data item
                    System.out.println(result.getDataItem());
                } else {
                    // Prints out error message
                    System.out.println("There is no definition for the word " + splitLine[1]);
                }

            // Sound: Plays a sound when the key is found (type 3)
            } else if(line.startsWith("sound")) {
                // Splits the string to take out the label
                String[] splitLine = line.split("\\s+");
                // Creates a new key to search for in the dictionary
                Key k = new Key(splitLine[1], 3);
                Record result = dict.get(k);
                // Checks if the label exists in the dictionary
                if(result != null) {
                    // Plays the sound
                    try {
                        SoundPlayer player = new SoundPlayer();
                        player.play(result.getDataItem());

                    // Catches any exception and prints out a message
                    } catch(MultimediaException e) {
                        System.out.println("Error: Wrong sound file for " + splitLine[1]);
                    }

                } else {
                    // Prints out error message
                    System.out.println("There is no sound file for " + splitLine[1]);
                }

            // Play: Plays music when the key is found (type 4)
            } else if(line.startsWith("play")) {
                // Splits the string to take out the label
                String[] splitLine = line.split("\\s+");
                // Creates a new key to search for in the dictionary
                Key k = new Key(splitLine[1], 4);
                Record result = dict.get(k);
                // Checks if the label exists in the dictionary
                if(result != null) {
                    // Plays the sound
                    try {
                        SoundPlayer player = new SoundPlayer();
                        player.play(result.getDataItem());

                    // Catches any exception and prints out a message
                    } catch(MultimediaException e) {
                        System.out.println("Error: Wrong music file for " + splitLine[1]);
                    }

                } else {
                    // Prints out error message
                    System.out.println("There is no music file for " + splitLine[1]);
                }

            // Say: Plays a human voice when the key is found (type 5)
            } else if(line.startsWith("say")) {
                // Splits the string to take out the label
                String[] splitLine = line.split("\\s+");
                // Creates a new key to search for in the dictionary
                Key k = new Key(splitLine[1], 5);
                Record result = dict.get(k);
                // Checks if the label exists in the dictionary
                if(result != null) {
                    // Plays the sound
                    try {
                        SoundPlayer player = new SoundPlayer();
                        player.play(result.getDataItem());

                    // Catches any exception and prints out a message
                    } catch(MultimediaException e) {
                        System.out.println("Error: Wrong voice file for " + splitLine[1]);
                    }

                } else {
                    // Prints out error message
                    System.out.println("There is no voice file for " + splitLine[1]);
                }

            // Show: Shows an image when the key is found (type 6)
            } else if(line.startsWith("show")) {
                // Splits the string to take out the label
                String[] splitLine = line.split("\\s+");
                // Creates a new key to search for in the dictionary
                Key k = new Key(splitLine[1], 6);
                Record result = dict.get(k);
                // Checks if the label exists in the dictionary
                if(result != null) {
                    // Shows the image
                    try {
                        PictureViewer viewer = new PictureViewer();
                        viewer.show(result.getDataItem());

                    // Catches any exception and prints out a message
                    } catch(MultimediaException e) {
                        System.out.println("Error: Wrong image file for " + splitLine[1]);
                    }

                } else {
                    // Prints out error message
                    System.out.println("There is no image file for " + splitLine[1]);
                }

            // Animate: Shows a gif when the key is found (type 7)
            } else if(line.startsWith("animate")) {
                // Splits the string to take out the label
                String[] splitLine = line.split("\\s+");
                // Creates a new key to search for in the dictionary
                Key k = new Key(splitLine[1], 7);
                Record result = dict.get(k);
                // Checks if the label exists in the dictionary
                if(result != null) {
                    // Shows the image
                    try {
                        PictureViewer viewer = new PictureViewer();
                        viewer.show(result.getDataItem());

                    // Catches any exception and prints out a message
                    } catch(MultimediaException e) {
                        System.out.println("Error: Wrong animated image file for " + splitLine[1]);
                    }

                } else {
                    // Prints out error message
                    System.out.println("There is no animated image file for " + splitLine[1]);
                }

            // Browse: Shows a URL when the key is found (type 8)
            } else if(line.startsWith("browse")) {
                // Splits the string to take out the label
                String[] splitLine = line.split("\\s+");
                // Creates a new key to search for in the dictionary
                Key k = new Key(splitLine[1], 8);
                Record result = dict.get(k);
                // Checks if the label exists in the dictionary
                if(result != null) {
                    // Shows the URL
                    ShowHTML browser = new ShowHTML();
                    browser.show(result.getDataItem());

                } else {
                    // Prints out error message
                    System.out.println("There is no webpage called " + splitLine[1]);
                }

            // Remove: Removes a dictionary item
            } else if(line.startsWith("remove")) {
                // Splits the string to take out the label
                String[] splitLine = line.split("\\s+");
                // Takes the type and converts into an int
                int t = Integer.parseInt(splitLine[2]);
                // Creates a new key to search for in the dictionary
                Key k = new Key(splitLine[1], t);
                // Tries to remove from dictionary
                try {
                    dict.remove(k);

                } catch(DictionaryException e) {
                    System.out.println("No record in the ordered dictionary has key (" + splitLine[1] + "," + splitLine[2] + ").");
                }

            // Add: Adds a dictionary item
            } else if(line.startsWith("add")) {
                // Splits the string to take out the label
                String[] splitLine = line.split("\\s+");
                // Takes the type and converts into an int
                int t = Integer.parseInt(splitLine[2]);
                // Creates a new key to search for in the dictionary
                Key k = new Key(splitLine[1], t);
                // Concatenates everything after type into a string
                String d = "";
                for(int i=3; i<splitLine.length; i++) {
                    // Formatting
                    if(i == splitLine.length-1) {
                        d = d + splitLine[i];

                    } else {
                        d = d + splitLine[i] + " ";
                    }
                }
                // Makes new record
                Record r = new Record(k, d);
                // Tries to remove from dictionary
                try {
                    dict.put(r);

                } catch(DictionaryException e) {
                    System.out.println("A record with the given key (" + splitLine[1] + "," + splitLine[2] + ") is already in the ordered dictionary.");
                }

            // List: Prints out all the labels in the dictionary with the specified prefix
            } else if(line.startsWith("list")) {
                // Splits the string to take out the label
                String[] splitLine = line.split("\\s+");
                // Sets r as the smallest node in the tree to start
                Record r = dict.smallest();
                // Found variable to tell if word has been found
                boolean found = false;

                // While loop to loop through the tree until r is null, then breaks out
                while(r != null) {
                    // Checks if the label of the key in r starts with the user entered string
                    if(r.getKey().getLabel().startsWith(splitLine[1])) {
                        // Prints out if label starts with user inputted prefix
                        System.out.print(r.getKey().getLabel() + " ");
                        found = true;
                    }

                    // Updates r
                    r = dict.successor(r.getKey());
                }

                // If not a single word with the prefix was found
                if(!found) {
                    System.out.print("No label attributes in the ordered dictionary start with prefix " + splitLine[1]);
                }

                // New line for formatting
                System.out.print("\n");

            // First: Prints out the smallest item in dictionary
            } else if(line.equals("first")) {
                Record r = dict.smallest();
                System.out.println(r.getKey().getLabel() + ", " + r.getKey().getType() + ", " + r.getDataItem());

            // Last: Prints out the largest item in dictionary
            } else if(line.equals("last")) {
                Record r = dict.largest();
                System.out.println(r.getKey().getLabel() + ", " + r.getKey().getType() + ", " + r.getDataItem());

            // If user enters invalid command
            } else {
                System.out.println("Invalid command.");
            }
        }

    }

}
