import java.io.*;

public class DoublesReaderApp{

   public static void main(String[] args) throws IOException{
      File data = new File("doubles.txt");
      BufferedReader in = new BufferedReader(
                          new FileReader(data));
      String line = in.readLine();
      while(line != null){
         double number = Double.parseDouble(line);
         System.out.println("Double: " + number);
         line = in.readLine();
      }
      in.close();

   }

}