import java.io.*;
import javax.swing.JOptionPane;

public class ExampleTwoTest{
   public static void main(String[] args){
      try{
         long length = getFileLength();
         System.out.println(length);
      }
      catch(IOException e){
         System.out.println("File couldn't be closed properly");
      }
   }
   public static long getFileLength()throws IOException{
      RandomAccessFile in = null;
      long len = 0;
      try{
          in = new RandomAccessFile("books.dat", "r");
          len = in.length();
      }
       catch(FileNotFoundException e){
          JOptionPane.showMessageDialog(null, "books.dat not found.\n"
               + "System will exit.", "Error", JOptionPane.ERROR_MESSAGE);
          System.exit(1);
      }
      catch(IOException e){
          JOptionPane.showMessageDialog(null, "I/O exception.\n"
               + "System will exit.", "Error", JOptionPane.ERROR_MESSAGE);
          System.exit(2);
      }
      finally{
          in.close();
      }
      return len;
    }
}
