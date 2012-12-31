import java.io.*;

public class BinaryWriterApp{
   public static void main(String[] args) throws IOException{
      String[] names = {"Vicky Lewis", "Karen Doe", "Greg Smith"};
     int[] grades = {94, 91, 86};

     File data = new File("grades.dat");
     DataOutputStream out = new DataOutputStream(
                            new BufferedOutputStream(
                            new FileOutputStream(data)));

     int numberOfRecords = names.length;
     out.writeInt(numberOfRecords);

     for (int i = 0; i < numberOfRecords; i++){
        out.writeUTF(names[i]);
        out.writeInt(grades[i]);
     }
     out.close();

   }
}
