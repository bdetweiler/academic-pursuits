import java.io.*;

public class BinaryReaderApp{
   public static void main(String[] args) throws IOException{

		File data = new File("strings.dat");
		DataInputStream in = new DataInputStream(
		                     new BufferedInputStream(
		                     new FileInputStream(data)));

		String string1 = in.readUTF();
		System.out.print(string1);

		String string2 = "";
		int bytes = in.available();
		int characters = (bytes)/2;
		for (int i = 0; i < characters; i++){
		   char c = in.readChar();
		   string2 += c;
		}
		System.out.print(string2);

		in.close();

    }
}
