import java.io.*;

public class FileTest{
   public static void main(String[] args){
      try{
        File file = new File("newdata.txt");
        file.createNewFile();
        if (file.exists()){
           System.out.println("The " + file.getName() + " exists.");
        }
        else
           System.out.println("The " + file.getName() + " doesn't exist.");
       }
       catch(IOException e){
         System.err.println(e.getMessage());
      }
   }
}