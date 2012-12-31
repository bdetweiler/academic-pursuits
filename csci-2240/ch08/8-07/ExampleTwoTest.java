public class ExampleTwoTest{
   public static void main(String[] args){
      outerLoop:
      for(int i = 1; i < 20; i++){
         for(int j = 2; j < i-1; j++){
            int remainder = i%j;
            if (remainder == 0)
               continue outerLoop;
         }
         System.out.println(i);
      }
   }
}