public class GenericPrinter <T> {

    // thingToPrint variable
    T thingToPrint;

    // Constructor
    public GenericPrinter(T thingToPrint) {

        this.thingToPrint = thingToPrint;
    }

    // print method
    public void print() {

        System.out.println(thingToPrint);
    }

}
