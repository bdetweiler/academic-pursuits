public class ExampleOneTest{
   public static void main(String[] args){
      int[][] table = new int[3][3];
      for (int i = 0; i < table.length; i++){
            for (int j = 0; j < table[i].length; j++){
            if (i == j)
                 table[i][j] = 1;
               else
                 table[i][j] = 0;
          }
      }
      String tableString = "";
      for (int i = 0; i < table.length; i++){
            for (int j = 0; j < table[i].length; j++){
            tableString += table[i][j] + " ";
            }
            tableString += "\n";
      }
      System.out.println(tableString);
   }
}
