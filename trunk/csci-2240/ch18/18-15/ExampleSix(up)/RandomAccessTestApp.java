import java.io.*;

public class RandomAccessTestApp{
   public static void main(String[] args) throws IOException{

      RandomAccessFile randomFile = new RandomAccessFile("grades.dat", "rw");
      final int NAME_LENGTH = 15;
      final int RECORD_LENGTH = NAME_LENGTH * 2 + 4;

      int recordNumber = 3;
      randomFile.seek((recordNumber - 1) * RECORD_LENGTH);
      StringHelper.writeString(randomFile, "Karen Tanner", NAME_LENGTH);


   }
}