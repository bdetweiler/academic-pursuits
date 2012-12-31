import java.io.*;
import java.util.*;

public class TokenReaderApp{

   public static void main(String[] args) throws IOException{
      String record = "WARP\tWar and Peace\t14.95";
      String tokenDelimiter = "\t\n";
      StringTokenizer t = new StringTokenizer(record, tokenDelimiter);
      int numberOfTokens = t.countTokens();
      System.out.println("Number of tokens: " + numberOfTokens);
      while (t.hasMoreTokens()){
         String token = t.nextToken();
         System.out.println(token);
      }
   }

}