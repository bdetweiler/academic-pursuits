public class EqualsTestApp2{
   public static void main(String[] args){
      BookOrder order1 = new BookOrder("WARP", 2);
      BookOrder order2 = new BookOrder("WARP", 2);
      if (order1.equals(order2))
         System.out.println("true");
      else
         System.out.println("false");
   }
}