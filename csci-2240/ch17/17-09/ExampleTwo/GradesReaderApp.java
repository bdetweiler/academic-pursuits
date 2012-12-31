import java.io.*;
import java.util.*;

public class GradesReaderApp{

   public static void main(String[] args) throws IOException{
      File data = new File("grades.txt");
      BufferedReader in = new BufferedReader(
                          new FileReader(data));
      String line = in.readLine();
      while (line != null){
         StringTokenizer t = new StringTokenizer(line, "|");
         String name = t.nextToken();
         String gradeString = t.nextToken();
         int grade = Integer.parseInt(gradeString);
         System.out.println(name + " " + grade);
         line = in.readLine();
      }
      in.close();

   }

}