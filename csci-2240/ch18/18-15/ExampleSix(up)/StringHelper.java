import java.io.*;

public class StringHelper{

   public static void writeString(DataOutput out, String s,
   int length) throws IOException{
      for (int i = 0; i < length; i++){
         if (i < s.length())
            out.writeChar(s.charAt(i));
         else
            out.writeChar(0);
      }
   }

   public static String readString(DataInput in, int length)
   throws IOException{
      String s = "";
      int i = 0;
      while (i < length){
         char c = in.readChar();
         if (c != 0)
            s += c;
         i++;
      }
      return s;
   }
}
