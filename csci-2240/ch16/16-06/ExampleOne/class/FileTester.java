import java.io.*;

public class FileTester{

   public static void main(String[] args) throws IOException{
      File file = new File("../files/books.txt");
      if (file.exists()){
         System.out.println("File name:      " + file.getName());
         System.out.println("Path:           " + file.getPath());
         System.out.println("Canonical path: " + file.getCanonicalPath());
         System.out.println("Absolute path:  " + file.getAbsolutePath());
         System.out.println("Is writable:    " + file.canWrite());
      }
      else
         System.out.println("The file " + file.getName() + " doesn't exist.");
   }
}
