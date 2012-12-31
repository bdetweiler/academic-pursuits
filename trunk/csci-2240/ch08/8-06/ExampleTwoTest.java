public class ExampleTwoTest{
   public static void main(String[] args){
   outerLoop:
      for (int i = 1; i < 4; i++){
         System.out.println("Outer " + i);
         while (true){
            int number = (int) (Math.random() * 10);
            System.out.println("   Inner " + number);
            if (number > 7){
               System.out.println("   This number is greater than 7");
               break outerLoop;
            }
         }
      }

}
}