public class Matrix {

    // Instance variables
    private int numRows;
    private int numCols;
    private double[][] data;

    // Constructor methods
    public Matrix(int r, int c) {
        // Initializing the instance variables
        numRows = r;
        numCols = c;
        data = new double[r][c];
    }

    public Matrix(int r, int c, double[] linArr) {
        // Initializing the instance variables
        numRows = r;
        numCols = c;
        data = new double[r][c];

        // Counter variable
        int counter = 0;
        // Converting a 1D array into a 2D array
        for(int i=0; i<numRows; i++) {
            for(int j=0; j<numCols; j++) {
                if(counter == linArr.length) {
                    break;
                }
                data[i][j] = linArr[counter];
                counter++;
            }
        }
    }

    // Getter methods
    public int getNumRows() {
        return numRows;
    }

    public int getNumCols() {
        return numCols;
    }

    public double[][] getData() {
        return data;
    }

    public double getElement(int r, int c) {
        return data[r][c];
    }

    // Setter method
    public void setElement(int r, int c, double value) {
        data[r][c] = value;
    }

    // Flips the rows and columns of the matrix and stores original values into new matrix
    public void transpose() {
        double[][] transposedMatrix = new double[numCols][numRows];
        int transposedRows = numCols;
        int transposedCols = numRows;

        for(int i=0; i<transposedRows; i++) {
            for(int j=0; j<transposedCols; j++) {
                transposedMatrix[i][j] = data[j][i];
            }
        }

        // Updates instance variables to match the new array dimensions
        data = transposedMatrix;
        numRows = transposedRows;
        numCols = transposedCols;
    }

    // Multiplies the matrix inputted by the scalar inputted
    public Matrix multiply(double scalar) {
        // Copying this.data values into an 1D array
        double[] newArr = new double[numRows * numCols];

        int colSize = numCols;

        // Multiplying values by scalar and saving into a 1D array
        for(int i=0; i<numRows; i++) {
            for(int j=0; j<colSize; j++) {
                newArr[(i*colSize) + j] = (data[i][j] * scalar);
            }
        }

        // Returning a new Matrix object with multiplied matrix as the data
        return new Matrix(numRows, numCols, newArr);
    }

    // Multiplies a matrix by another matrix
    public Matrix multiply(Matrix other) {
        if(numCols != other.getNumRows()) {
            return null;
        } else {
            // Empty Arrays
            double[][] tempArr = new double[numRows][other.getNumCols()];
            double[] newArr = new double[numRows * other.getNumCols()];

            // Multiplying values by other matrix and saving into a 1D array
            for(int i=0; i<numRows; i++) {
                for(int j=0; j<other.getNumCols(); j++) {
                    for(int k=0; k<numCols; k++) {
                        tempArr[i][j] += data[i][k] * other.getElement(k, j);
                    }
                }
            }

            int colSize = other.getNumCols();

            // Saving into a 1D array
            for(int i=0; i<numRows; i++) {
                for(int j=0; j<colSize; j++) {
                    newArr[(i * colSize) + j] = tempArr[i][j];
                }
            }

            // Returning a new Matrix object with multiplied matrix as the data
            return new Matrix(this.numRows, other.getNumCols(), newArr);
        }
    }

    // toString method that prints out the formatted matrix
    public String toString() {
        // Checking if matrix is completely empty
        int counter = 0;

        for(int i=0; i<numRows; i++) {
            for(int j=0; j<numCols; j++) {
                if(data[i][j] != 0.0) {
                    // Breaks out of the loop if it finds a double that is not 0.0
                    break;
                } else {
                    counter ++;
                }
            }
        }

        // If the number of elements in the array is all 0.0
        if(counter == (numRows*numCols)) {
            // Returns empty matrix if all values in matrix are 0.0
            return "Empty matrix";
        }

        // Empty string
        String S = "";
        String d;
        // Printing out matrix if array is not empty
        for(int i=0; i<numRows; i++) {
            for(int j=0; j<numCols; j++) {
                if(j == numCols-1) {
                    d = String.format("%.3f", data[i][j]);
                    S = S + String.format("%8s\n", d);
                } else {
                    d = String.format("%.3f", data[i][j]);
                    S = S + String.format("%8s", d);
                }
            }
        }

        // Returns the formatted string S
        return S;
    }

}
