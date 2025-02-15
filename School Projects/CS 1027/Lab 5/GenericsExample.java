/**
 * 
 */

/**
 * @author MaxMicro
 *
 */
public class GenericsExample {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		//IntegerPrinter iPrinter = new IntegerPrinter(23);
		//iPrinter.print();
		
		//DoublePrinter dPrinter = new DoublePrinter(3.32);
		//dPrinter.print();
		
		//StringPrinter sPrinter = new StringPrinter("Niblick");
		//sPrinter.print();

		System.out.println("\nGeneric Printer\n");
		
		GenericPrinter<Integer> giPrinter = new GenericPrinter<>(23);
		giPrinter.print();
		
		GenericPrinter<Double> gdPrinter = new GenericPrinter<>(3.32);
		gdPrinter.print();
		
		GenericPrinter<String> gsPrinter = new GenericPrinter<>("Niblick");
		gsPrinter.print();

	}

}
