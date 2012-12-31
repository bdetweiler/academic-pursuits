import java.text.NumberFormat;

public class ExampleThreeTest{
   public static void main(String[] args){
      double miles = 15341.256;
      NumberFormat number = NumberFormat.getNumberInstance();
      number.setMaximumFractionDigits(1);
      String milesString = number.format(miles);          // returns 15,341.3

      System.out.println(milesString);
   }
}
