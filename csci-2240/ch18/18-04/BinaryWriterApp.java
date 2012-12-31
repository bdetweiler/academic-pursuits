import java.io.*;

public class BinaryWriterApp{
   public static void main(String[] args) throws IOException{
      File data = new File("example.dat");
      DataOutputStream out = new DataOutputStream(
                             new BufferedOutputStream(
                             new FileOutputStream(data)));
      out.writeInt(5);
      out.writeChar('c');
      out.writeBoolean(true);
      out.writeUTF("Java");
      out.writeChar('\n');
      out.writeChars("End of file");
      out.close();
   }
}
