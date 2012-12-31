import java.io.*;

public class RandomAccessWriterApp{

   public static void main(String[] args) throws IOException{
      String[] codes = {"WARP", "MBDK", "CITR", "WUTH"};
      double[] prices = {14.95, 12.95, 9.95, 12.95};
      RandomAccessFile out = new RandomAccessFile("books.dat", "rw");
      for (int i = 0; i < codes.length; i++){
         out.writeChars(codes[i]);
         out.writeDouble(prices[i]);
      }
      out.close();
   }
}
