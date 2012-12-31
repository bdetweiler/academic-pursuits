import java.util.*;

public class CompareTestApp{
   public static void main(String args[]){
      BookOrder[] bookOrder = new BookOrder[3];
      bookOrder[0] = new BookOrder("warp", 2);
      bookOrder[1] = new BookOrder("mbdk", 3);
      bookOrder[2] = new BookOrder("warp", 1);
      Arrays.sort(bookOrder);
      for (int i = 0; i < bookOrder.length; i++){
         System.out.println(bookOrder[i]);
      }
   }
}
