import java.io.*;

public class BinaryWriterApp{
   public static void main(String[] args) throws IOException{
      File data = new File("strings.dat");
	  DataOutputStream out = new DataOutputStream(
	                         new BufferedOutputStream(
	                         new FileOutputStream(data)));

	  out.writeUTF("How many bytes are in this string?\n");
	  int size1 = out.size();

	  out.writeChars("How many bytes are in this string?\n");
	  int size2 = out.size() - size1;

	  out.close();

	  System.out.println("The writeUTF method writes " + size1 + " bytes.");
	  System.out.println("The writeChars method writes " + size2 + " bytes.");


   }
}
