public class ExampleTwoTest{
   public static void main(String[] args){
      int[][] pyramid = new int[4][];
      for (int i = 0; i < pyramid.length; i++){
         pyramid[i] = new int[i+1];
      }
      String pyramidString = "";
      for (int i = 0; i < pyramid.length; i++){
         for (int j = 0; j < pyramid[i].length; j++){
               pyramidString += "["+ i + "]" + "["+ j + "]" + " ";
            }
            pyramidString += "\n";
      }
      System.out.println(pyramidString);
   }
}
