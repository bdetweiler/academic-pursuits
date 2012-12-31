import java.io.*;

public class TextReaderApp{
   public static void main(String[] args) throws IOException{
      File data = new File("example.txt");
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
         System.out.println("File not found - example.txt");
   }
}
