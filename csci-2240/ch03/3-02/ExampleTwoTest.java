import java.text.NumberFormat;

public class ExampleTwoTest{
   public static void main(String[] args){
      double majority = .512;
      NumberFormat percent = NumberFormat.getPercentInstance();
      String majorityString = percent.format(majority);   // returns 51%

      System.out.println(majorityString);
   }
}
