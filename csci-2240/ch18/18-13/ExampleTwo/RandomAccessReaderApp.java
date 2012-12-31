import java.io.*;

public class RandomAccessReaderApp{

   public static void main(String[] args) throws IOException{
      RandomAccessFile in = new RandomAccessFile("books.dat", "r");
      int recordNumber = 3;
      int recordLength = 4*2 + 8;
      in.seek((recordNumber-1) * (recordLength));
      String code = "";
      for (int i = 0; i < 4; i++){
         char c = in.readChar();
         code += c;
      }
      double price = in.readDouble();
      in.close();
      System.out.println(code);
      System.out.println(price);
   }
}
