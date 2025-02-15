public class BankAccount {

    public double balance;

    public BankAccount(double initialAmount) {
        balance = initialAmount;
    }

    public double getBalance(){
        return balance;
    }

    public void deposit (double amount) {
        balance = balance + amount;
    }

    public void withdraw(double amount) {
        if (amount <= balance)
            balance = balance - amount;
        else
            System.out.println("Insufficient funds for withdrawal of $" + amount);
    }

    public String toString(){
        return ("BankAccount: balance $" + balance);
    }
}
