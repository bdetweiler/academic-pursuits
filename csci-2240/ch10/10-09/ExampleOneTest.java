public class ExampleOneTest{
   public static void main(String[] args){
      int[] values = {93, 95, 87, 92};
      int ave = getAverage(values);

   }
   public static int getAverage(int[] values){
         System.out.println("enter getAverage method");    //debug code
         int sum = 0;
         for (int i = 0; i < values.length; i++){
         sum = values[i];
            System.out.println("i: " + i);                 //debug code
            System.out.println("values[i]: " + values[i]); //debug code
         }
         int average = sum/values.length;
         System.out.println("sum: " + sum);                //debug code
         System.out.println("average: " + average);        //debug code
         System.out.println("leave getAverage method");    //debug code
         return average;
   }
}
