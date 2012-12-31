public class FinancialCalculations{

   public static double calculateMonthlyPayment(double loanAmount,
   int months, double monthlyInterestRate){
      double monthlyPayment = loanAmount * monthlyInterestRate/
         (1 - 1/Math.pow(1+monthlyInterestRate, months));
      return monthlyPayment;
   }

   public static double calculateFutureValue(double monthlyPayment,
   int months, double monthlyInterestRate){
      int i = 1;
      double futureValue = 0;
      while (i <= months) {
         futureValue = (futureValue + monthlyPayment) *
         (1 + monthlyInterestRate);
         i++;
      }
      return futureValue;
   }
   public static double calculateLoanAmount(double monthlyPayment,
      int months, double monthlyInterestRate){
      double amount = (monthlyPayment*(1-1/(Math.pow((1+monthlyInterestRate),
              months))))/monthlyInterestRate;
      return amount;
  }
}
