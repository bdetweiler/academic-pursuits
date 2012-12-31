import java.io.*;
public class FileTest{
   public static void main(String[] args){
   try{
      File data = new File("grades.txt");
      if (data.exists()){
         BufferedReader in = new BufferedReader(
                             new FileReader(data));
         String line = in.readLine();
         while(line != null){
            System.out.println(line);
            line = in.readLine();
         }
         in.close();
      }
      else
         System.out.println("The grades.txt file doesn't exist");
   }
   catch(IOException e){
      System.out.println("An IOException has occurred.");
   }
   }
}