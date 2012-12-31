import java.text.NumberFormat;

public class ExampleTwoTest{
   public static void main(String[] args){
   double loanAmount = 12000;
   double monthlyPayment = 0;
   String table = "";
   String row = "";
   NumberFormat currency = NumberFormat.getCurrencyInstance();
   NumberFormat percent = NumberFormat.getPercentInstance();
   percent.setMinimumFractionDigits(1);

   table  = "    ";
   for (double interestRate = 5.0; interestRate < 8.0; interestRate += .5){
      table += percent.format(interestRate/100) + "       ";
   }
   table += "\n";

   for (int years = 4; years > 1; years--){
      row = years + "   ";
      for (double interestRate = 5.0; interestRate < 8.0; interestRate += .5){
         int months = years * 12;
         double monthlyInterestRate = interestRate/12/100;
         monthlyPayment = FinancialCalculations.calculateMonthlyPayment(
            loanAmount, months, monthlyInterestRate);
         row += currency.format(monthlyPayment) + "    ";
      }
      table += row + "\n";
      row = "";
   }
   System.out.println(table);

   }
}
