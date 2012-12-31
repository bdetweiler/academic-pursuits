import java.io.*;

public class RootLister{
   public static void main(String[] args) throws IOException{
      File[] myRoots = File.listRoots();
      for (int i = 0; i < myRoots.length; i++){
         System.out.println(myRoots[i].getPath());
      }
   }
}
