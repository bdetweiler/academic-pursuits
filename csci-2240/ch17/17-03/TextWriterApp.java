import java.io.*;

public class TextWriterApp{
   public static void main(String[] args) throws IOException{
      File data = new File("example.txt");
      PrintWriter out = new PrintWriter(
                        new BufferedWriter(
                        new FileWriter(data)));
      out.print(5);
      out.print('c');
      out.print(true);
      out.println("Java");
      out.print("End of file");
      out.close();

   }
}
