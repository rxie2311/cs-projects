public class CheckingAccount extends BankAccount {

    private int transactionCount;

    private static final int FREE_TRANSACTIONS = 3;
    private static final double TRANSACTION_FEE = 2.0;
    
    public CheckingAccount(double initialAmount) {
        super(initialAmount);
        transactionCount = 0;
    }

    public CheckingAccount() {
        super(0.0);
        transactionCount = 0;
    }

    public int getTransactionCount() {
        return transactionCount;
    }

    public void deposit(double amount) {
        transactionCount++;
        super.deposit(amount);
    }

    public void withdraw(double amount) {
        transactionCount++;
        super.withdraw(amount);
    }
    
    public void deductFees() {
        if (transactionCount > FREE_TRANSACTIONS) {
            double fees = TRANSACTION_FEE * (transactionCount - FREE_TRANSACTIONS);
            super.withdraw(fees);
        }
        transactionCount = 0;
    }

    public String toString() {
        return ("CheckingAccount: balance $" + getBalance() + ", transactions " + transactionCount);
    }
}
