public class MarkovChain {

    // Instance Variables
    private Vector stateVector;
    private Matrix transitionMatrix;

    // Constructor method
    public MarkovChain(Vector sVector, Matrix tMatrix) {
        // Initializing variables
        stateVector = sVector;
        transitionMatrix = tMatrix;
    }

    // Checking if variables are valid for Markov's chain
    public boolean isValid() {
        // Variables
        double sum = 0.0;
        double mSum = 0.0;
        int counter = 0;
        // Checking if the matrix is square
        if(transitionMatrix.getNumRows() == transitionMatrix.getNumCols()) {
            // Checking if matrix dimensions are equal to no. of columns in vector
            if(transitionMatrix.getNumCols() == stateVector.getNumCols()) {
                // Checking if sum of vector column is 1.0
                for(int i=0; i<stateVector.getNumCols(); i++) {
                    sum += stateVector.getElement(i);
                }
                if(sum > 0.99 && sum < 1.01) {
                    // Checking if sum of each row in matrix is 1.0
                    for(int i=0; i<transitionMatrix.getNumRows(); i++) {
                        for(int j=0; j<transitionMatrix.getNumCols(); j++) {
                            mSum += transitionMatrix.getElement(i, j);
                            System.out.println(mSum);
                        }
                        if(mSum > 0.99 && mSum < 1.01) {
                            counter++;
                            System.out.println(counter);
                        }
                        mSum = 0;
                    }
                    if(counter == transitionMatrix.getNumRows()) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    // Checking probability matrix
    public Matrix computeProbabilityMatrix(int numSteps) {
        // Check if variables are valid
        if(!this.isValid()) {
            // Returns null if invalid
            return null;
        }

        // Empty variable to store the result
        Matrix m = transitionMatrix;
        // Multiplying matrix by itself numSteps-1 times
        for(int i=0; i<numSteps-1; i++) {
            m = transitionMatrix.multiply(m);
        }
        // Multiplying matrix by vector
        m = stateVector.multiply(m);

        return m;
    }

}
