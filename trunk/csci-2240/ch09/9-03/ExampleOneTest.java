public class ExampleOneTest{
   public static void main(String[] args){
      double[] prices = {14.95, 12.95, 11.95, 9.95};
      double sum = 0.0;
      for (int i = 0; i < prices.length; i++){
         sum += prices[i];
         System.out.println(prices[i]);
      }
      double average = sum/prices.length;
      System.out.println("Average: " + average);
   }
}
