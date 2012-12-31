import java.io.*;

public class DirLister{

   public static void main(String[] args) throws IOException{
      File dir = new File("C:/java/ch16/classes");
      if ((dir.exists()) && (dir.isDirectory())){
         System.out.println("Directory: " + dir.getCanonicalPath());
         String[] files = dir.list();
         for (int i = 0; i < files.length; i++){
            System.out.println(files[i]);
         }
      }
   }
}
