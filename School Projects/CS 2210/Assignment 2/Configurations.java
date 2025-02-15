/*
 * Name: Raymond Xie
 * Student No: 251275727
 * Program: Configurations
 * Description: Methods to help regulate the game being played.
 */

public class Configurations {

    // Instance variables:
    private int board_size;
    private int lengthToWin;
    private int max_levels;
    private char[][] board;

    // Constructor method
    public Configurations (int board_size, int lengthToWin, int max_levels) {
        // Saving input into instance variables
        this.board_size = board_size;
        this.lengthToWin = lengthToWin;
        this.max_levels = max_levels;
        // Creating new instance variable
        board = new char[this.board_size][this.board_size];
        // Storing space in array
        for(int i=0; i<this.board_size; i++) {
            for(int j=0; j<this.board_size; j++) {
                // Saves a space into each position of the array
                board[i][j] = ' ';
            }
        }
    }

    // Public methods:
    // Creates an empty hash dictionary
    public HashDictionary createDictionary() {
        // Creating new hash dictionary w/ size 10,000
        HashDictionary dict = new HashDictionary(10000);
        // Returns hash dictionary
        return dict;
    }

    // Stores characters in board into the hash dictionary
    public int repeatedConfiguration(HashDictionary hashTable) {
        // Variable to store board
        String config = "";
        // For loop to cycle through the array and save into a string
        for(int i=0; i<board_size; i++) {
            for(int j=0; j<board_size; j++) {
                // Concatenates into 1 string
                config = config + board[i][j];
            }
        }

        // Checking if config is already inside the hash table
        int result = hashTable.get(config);
        // If get returns -1 (means it is not in the hash table), returns -1
        if(result == -1) {
            return -1;

        // Else, it returns the score associated
        } else {
            return result;
        }
    }

    // Inserts board and score into a hash dictionary
    public void addConfiguration(HashDictionary hashDictionary, int score) {
        // Variable to store board
        String config = "";
        // For loop to cycle through the array and save into a string
        for(int i=0; i<board_size; i++) {
            for(int j=0; j<board_size; j++) {
                // Concatenates into 1 string
                config = config + board[i][j];
            }
        }

        // Saving it into a hash dictionary
        Data record = new Data(config, score);
        hashDictionary.put(record);
    }

    // Stores a symbol into the board array
    public void savePlay(int row, int col, char symbol) {
        // Storing symbol into the array
        board[row][col] = symbol;
    }

    // Checks if a square is empty
    public boolean squareIsEmpty(int row, int col) {
        // If ' ' is found, returns true (square is empty)
        if(board[row][col] == ' ') {
            return true;

        // If ' ' is not found, returns false (square is not empty)
        } else {
            return false;
        }
    }

    // Checks for a X or + shape on the board
    public boolean wins(char symbol) {
        // Checks for X shape
        if(xShape(symbol, lengthToWin)) {
            return true;
        }
        // Checks for + shape
        if(plusShape(symbol, lengthToWin)) {
            return true;
        }

        // If none are found, return false
        return false;
    }

    // Checks if board is full and no one has won
    public boolean isDraw() {
        // Loops through the whole board checking for ' '
        for(int i=0; i<board_size; i++) {
            for(int j=0; j<board_size; j++) {
                if(board[i][j] == ' ') {
                    return false;
                }
            }
        }

        // Checks if the game has already been won
        if(wins('X') || wins('O')) {
            return false;
        }

        // If game has not been won and board is full, return true
        return true;
    }

    // Evaluates the board and returns a value based on who won
    public int evalBoard() {
        // If computer wins: Returns 3
        if(wins('O')) {
            return 3;

        // If human wins: Returns 0
        } else if(wins('X')) {
            return 0;

        // If draw: Returns 2
        } else if(isDraw()) {
            return 2;
        }

        // If game is not over: Returns 1
        return 1;
    }

    // Private methods:
    // Checks if there is an X shape
    private boolean xShape(char symbol, int lengthToWin) {
        // Integer value that will keep track of how many symbols were in the x shape
        int xCount;
        // Loop to loop through the board
        for(int i=0; i<board_size; i++) {
            for(int j=0; j<board_size; j++) {
                // Checks for the symbol in board
                if(board[i][j] == symbol) {
                    // Makes sure diagonals are not out of bounds
                    if(!(i-1 < 0) && !(j-1 < 0) && !(i+1 >= board_size) && !(j+1 >= board_size)) {
                        // Checks if top-left, top-right, bot-left and bot-right are all symbol
                        if(board[i-1][j-1] == symbol && board[i-1][j+1] == symbol && board[i+1][j-1] == symbol && board[i+1][j+1] == symbol) {
                            // Updates the counter to 4
                            xCount = 4;
                            // Checks if game already won with k=4
                            if(xCount >= lengthToWin) {
                                return true;
                            }

                            // Checks each of the 4 diagonals for more symbols
                            int counter = 2;
                            // Top-left: Checks the entire top-left diagonal
                            while(!(i-counter < 0) && !(j-counter < 0)) {
                                if(board[i-counter][j-counter] == symbol) {
                                    // Updates xCount
                                    xCount++;
                                    // Checks if game is won
                                    if(xCount >= lengthToWin) {
                                        return true;
                                    }
                                }
                                // Adds 1 to counter if game has not been won and there are still more squares on the diagonal
                                counter++;
                            }

                            // Reset counter back to 2
                            counter = 2;
                            // Top-right: Checks the entire top-right diagonal
                            while(!(i-counter < 0) && !(j+counter >= board_size)) {
                                if(board[i-counter][j+counter] == symbol) {
                                    // Updates xCount
                                    xCount++;
                                    // Checks if game is won
                                    if(xCount >= lengthToWin) {
                                        return true;
                                    }
                                }
                                // Adds 1 to counter if game has not been won and there are still more squares on the diagonal
                                counter++;
                            }

                            // Reset counter back to 2
                            counter = 2;
                            // Bot-left: Checks the entire bot-left diagonal
                            while(!(i+counter >= board_size) && !(j-counter < 0)) {
                                if(board[i+counter][j-counter] == symbol) {
                                    // Updates xCount
                                    xCount++;
                                    // Checks if game is won
                                    if(xCount >= lengthToWin) {
                                        return true;
                                    }
                                }
                                // Adds 1 to counter if game has not been won and there are still more squares on the diagonal
                                counter++;
                            }

                            // Reset counter back to 2
                            counter = 2;
                            // Bot-right: Checks the entire bot-right diagonal
                            while(!(i+counter >= board_size) && !(j+counter >= board_size)) {
                                if(board[i+counter][j+counter] == symbol) {
                                    // Updates xCount
                                    xCount++;
                                    // Checks if game is won
                                    if(xCount >= lengthToWin) {
                                        return true;
                                    }
                                }
                                // Adds 1 to counter if game has not been won and there are still more squares on the diagonal
                                counter++;
                            }
                        }
                    }
                }
            }
        }

        // If game has not been won by the end of checking
        return false;
    }

    // Checks if there is a + shape
    private boolean plusShape(char symbol, int lengthToWin) {
        // Integer value that will keep track of how many symbols were in the x shape
        int plusCount;
        // Loop to loop through the board
        for(int i=0; i<board_size; i++) {
            for(int j=0; j<board_size; j++) {
                // Checks for the symbol in board
                if(board[i][j] == symbol) {
                    // Makes sure lines are not out of bounds
                    if(!(i-1 < 0) && !(j-1 < 0) && !(i+1 >= board_size) && !(j+1 >= board_size)) {
                        // Checks if top, bottom, right and left are all symbol
                        if(board[i-1][j] == symbol && board[i+1][j] == symbol && board[i][j+1] == symbol && board[i][j-1] == symbol) {
                            // Updates the counter to 4
                            plusCount = 4;
                            // Checks if game is won from k=4
                            if(plusCount >= lengthToWin) {
                                return true;
                            }

                            // Checks each of the 4 lines for more symbols
                            int counter = 2;
                            // Top: Checks the entire top line
                            while(!(i-counter < 0)) {
                                if(board[i-counter][j] == symbol) {
                                    // Updates plusCount
                                    plusCount++;
                                    // Checks if game is won
                                    if(plusCount >= lengthToWin) {
                                        return true;
                                    }
                                }
                                // Adds 1 to counter if game has not been won and there are still more squares on the line
                                counter++;
                            }

                            // Resets counter back to 2
                            counter = 2;
                            // Bottom: Checks the entire bottom line
                            while(!(i+counter >= board_size)) {
                                if(board[i+counter][j] == symbol) {
                                    // Updates plusCount
                                    plusCount++;
                                    // Checks if game is won
                                    if(plusCount >= lengthToWin) {
                                        return true;
                                    }
                                }
                                // Adds 1 to counter if game has not been won and there are still more squares on the line
                                counter++;
                            }

                            // Resets counter back to 2
                            counter = 2;
                            // Right: Checks the entire right line
                            while(!(j+counter >= board_size)) {
                                if(board[i][j+counter] == symbol) {
                                    // Updates plusCount
                                    plusCount++;
                                    // Checks if game is won
                                    if(plusCount >= lengthToWin) {
                                        return true;
                                    }
                                }
                                // Adds 1 to counter if game has not been won and there are still more squares on the line
                                counter++;
                            }

                            // Resets counter back to 2
                            counter = 2;
                            // Left: Checks the entire left line
                            while(!(j-counter < 0)) {
                                if(board[i][j-counter] == symbol) {
                                    // Updates plusCount
                                    plusCount++;
                                    // Checks if game is won
                                    if(plusCount >= lengthToWin) {
                                        return true;
                                    }
                                }
                                // Adds 1 to counter if game has not been won and there are still more squares on the line
                                counter++;
                            }
                        }
                    }
                }
            }
        }

        // If game has not been won by the end of checking
        return false;
    }

}


