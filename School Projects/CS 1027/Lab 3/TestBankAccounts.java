import java.io.*;

public class TestBankAccounts {

    public static void main(String[] args) {

        BankAccount bacc0 = new BankAccount(0);
        System.out.println(bacc0.toString());

        BankAccount bacc1 = new BankAccount(5000);
        System.out.println(bacc1.toString());

        BankAccount bacc2 = new CheckingAccount(200.0);

        CheckingAccount chacc1 = new CheckingAccount(500.0);
        System.out.println(chacc1.toString());

        SavingsAccount sacc1 = new SavingsAccount(1000.0, 1.0);
        System.out.println(sacc1.toString());

        //-------------------------------------------------------

        //bacc0 == chacc1

        //chacc1 == bacc1

        //chacc1 == bacc2

        ((CheckingAccount)bacc1).deductFees();
        ((CheckingAccount)chacc1).deductFees();
        //((CheckingAccount)sacc1).deductFees();



    }

}
