import java.text.NumberFormat;

public class ExampleTwoTest{
   public static void main(String[] args){
      double[] heights = {60, 62, 64, 66, 68, 70, 72, 74};
      NumberFormat number = NumberFormat.getNumberInstance();
      for (int i = 0; i < heights.length; i++){
          heights[i] *= 2.54;
          System.out.println(number.format(heights[i]) + " cm");
      }
   }
}
