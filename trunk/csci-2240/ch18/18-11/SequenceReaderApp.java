import java.io.*;

public class SequenceReaderApp{
   public static void main(String[] args) throws IOException{

      File data1 = new File("grades1.dat");
      File data2 = new File("grades2.dat");
      DataInputStream in = new DataInputStream(
                        new SequenceInputStream(
                        new FileInputStream(data1),
                        new FileInputStream(data2)));

      int numberOfRecords = in.readInt();
      for (int i = 0; i < 3; i++){
            System.out.println(in.readUTF()  + "\t" + in.readInt());
      }
      numberOfRecords = in.readInt();
      for (int i = 0; i < 3; i++){
            System.out.println(in.readUTF()  + "\t" + in.readInt());
      }
      in.close();
   }
}
