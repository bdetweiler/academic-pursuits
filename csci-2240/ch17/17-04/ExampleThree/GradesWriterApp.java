import java.io.*;

public class GradesWriterApp{

   public static void main(String[] args) throws IOException{
      String[] names = {"Vicky Lewis", "Karen Doe", "Greg Smith"};
      int[] grades = {94, 91, 86};
      File data = new File("grades.txt");
      PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter(data)));
      for (int i = 0; i<names.length; i++){  //loops through each record
          out.print(names[i]);
          out.print('|'); //places a bar between each field
          out.println(grades[i]); //places an end of line character after each record
      }
      out.close();

   }
}
