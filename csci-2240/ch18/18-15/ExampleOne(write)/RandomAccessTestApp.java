import java.io.*;

public class RandomAccessTestApp{
   public static void main(String[] args) throws IOException{

      RandomAccessFile randomFile = new RandomAccessFile("grades.dat", "rw");
      final int NAME_LENGTH = 15;
      final int RECORD_LENGTH = NAME_LENGTH * 2 + 4;

      String[] names = {"Vicky Lewis", "Karen Doe", "Greg Smith"};
      int[] grades = {94, 91, 86};
      for (int i = 0; i < names.length; i++){
         StringHelper.writeString(randomFile, names[i], NAME_LENGTH);
         randomFile.writeInt(grades[i]);
      }



   }
}