public class Vector extends Matrix {

    // Constructor method
    public Vector(int c) {
        super(1, c);
    }

    public Vector(int c, double[] linArr) {
        super(1, c, linArr);
    }

    // Getter method
    public double getElement(int c) {
        return super.getElement(0, c);
    }

}
