import javax.swing.*;
import java.text.*;

public class FutureValueApp{
   public static void main(String[] args){
      String choice = "";
      while (!(choice.equalsIgnoreCase("x"))){
         String paymentString = JOptionPane.showInputDialog(
            "Enter monthly payment: ");
         double monthlyPayment = Double.parseDouble(paymentString);

         String rateString = JOptionPane.showInputDialog(
            "Enter yearly interest rate: ");
         double interestRate = Double.parseDouble(rateString);
         double monthlyInterestRate = interestRate/12/100;

         String yearsString = JOptionPane.showInputDialog(
            "Enter number of years: ");
         int years = Integer.parseInt(yearsString);
         int months = years * 12;

         double futureValue = calculateFutureValue(monthlyPayment,
            months, monthlyInterestRate);

         NumberFormat currency = NumberFormat.getCurrencyInstance();
         NumberFormat percent = NumberFormat.getPercentInstance();
         percent.setMinimumFractionDigits(2);
         String message =
              "Monthly payment: " + currency.format(monthlyPayment) + "\n"
            + "Yearly interest rate: " + percent.format(interestRate/100) + "\n"
            + "Number of years: " +  years + "\n"
            + "Future value: " + currency.format(futureValue) + "\n\n"
            + "To continue, press Enter.\n"
            + "To exit, enter 'x': ";
         choice = JOptionPane.showInputDialog(null,
            message, "Future Value", JOptionPane.PLAIN_MESSAGE);
      }
      System.exit(0);
   }

   private static double calculateFutureValue(double monthlyPayment,
   int months, double interestRate){
      int i = 1;
      double futureValue = 0;
      while (i <= months) {
         futureValue = (futureValue + monthlyPayment) *
         (1 + interestRate);
         i++;
      }
      return futureValue;
   }
}