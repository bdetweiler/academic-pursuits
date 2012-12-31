import java.io.*;

public class RandomAccessTestApp{
   public static void main(String[] args) throws IOException{

      RandomAccessFile randomFile = new RandomAccessFile("grades.dat", "rw");
      final int NAME_LENGTH = 15;
      final int RECORD_LENGTH = NAME_LENGTH * 2 + 4;

      randomFile.setLength(randomFile.length() - RECORD_LENGTH);
      int numberOfRecords = (int) randomFile.length() / RECORD_LENGTH;
      System.out.println(numberOfRecords);


   }
}