import java.io.*;

public class BinaryReaderApp{
   public static void main(String[] args) throws IOException{
      File data = new File("example.dat");
      if (data.exists()){
         DataInputStream in = new DataInputStream(
                              new BufferedInputStream(
                              new FileInputStream(data)));

         int number = in.readInt();
         System.out.println(number);

         char letter = in.readChar();
         System.out.println(letter);

         boolean value = in.readBoolean();
         System.out.println(value);

         String string = in.readUTF();
         System.out.println(string);

         in.readChar();

         int numberOfChars = in.available()/2;
         String characters = "";
         for (int i = 0; i < numberOfChars; i++){
            char c = in.readChar();
            characters += c;
         }
         System.out.println(characters);

         in.close();

      }
   }
}
