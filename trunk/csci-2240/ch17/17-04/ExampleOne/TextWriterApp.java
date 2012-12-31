import java.io.*;

public class TextWriterApp{
   public static void main(String[] args) throws IOException{
       File data = new File("doubles.txt");
      PrintWriter out = new PrintWriter(
                        new BufferedWriter(
                        new FileWriter(data)));
      out.println(59.75);
      out.println(23.70);
      out.println(92.22);
      out.close();

   }
}
