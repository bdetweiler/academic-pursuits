import java.io.*;
import java.util.*;

public class LogWriterApp{

   public static void main(String[] args) throws IOException{
      PrintWriter out =    new PrintWriter(
                     new BufferedWriter(
                     new FileWriter("log.txt", true)));
      out.print("This application was run on ");
      Date today = new Date();
      out.println(today);
      out.close();
   }

}
