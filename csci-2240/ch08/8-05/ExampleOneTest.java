public class ExampleOneTest{
   public static void main(String[] args){
      String table = "";
      String row = "";
      for (int i = 1; i<4; i++){
         for (int j = 1; j< 4; j++){
            int number = (int) (Math.random() * 9);
            row += number + " ";
         }
         table += row + "\n";
         row = "";
      }
      System.out.println(table);
   }
}
