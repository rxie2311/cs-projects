public class SavingsAccount extends BankAccount {

    private static double interestRate;

    public SavingsAccount(double initialAmount, double rate) {
        super(initialAmount);
        interestRate = rate;
        balance = initialAmount;
    }

    public double getInterestRate() {
        return interestRate;
    }

    public void calculateInterest() {
        double amount = interestRate * super.getBalance();
        super.deposit(amount);
    }

    public String toString() {
        return ("SavingsAccount: balance $" + super.getBalance() + ", interest rate " + getInterestRate() + "%");
    }

    public static void main(String[] args) {
        SavingsAccount myAccount = new SavingsAccount(100.0,0.15);
        myAccount.calculateInterest();
        System.out.println(myAccount.toString());
    }

}

