public class FinancialCalculations{

   public static double calculateFutureValue(double monthlyPayment,
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

   public static double calculateMonthlyPayment(double loanAmount,
   int months, double monthlyInterestRate){
      double monthlyPayment = loanAmount * monthlyInterestRate/
                              (1 - 1/Math.pow(1+monthlyInterestRate, months));
      return monthlyPayment;
   }
}