import java.io.*;

public class BinaryReaderApp{
   public static void main(String[] args) throws IOException{

      File data = new File("grades.dat");
      DataInputStream in = new DataInputStream(
                            new BufferedInputStream(
                             new FileInputStream(data)));

      int numberOfRecords = in.readInt();

      for (int i = 0; i < numberOfRecords; i++){
            String name = in.readUTF();
            int grade = in.readInt();
            System.out.println(name + "\t" + grade);
      }
      in.close();
    }
}
