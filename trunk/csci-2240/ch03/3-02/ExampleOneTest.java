import java.text.NumberFormat;

public class ExampleOneTest{
   public static void main(String[] args){
      double price = 11.575;
      NumberFormat currency = NumberFormat.getCurrencyInstance();
      String priceString = currency.format(price);        // returns $11.58
      System.out.println(priceString);
   }
}
