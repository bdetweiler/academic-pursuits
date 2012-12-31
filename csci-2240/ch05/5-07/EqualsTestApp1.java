public class EqualsTestApp1{
   public static void main(String[] args){
      Book book1 = new Book("WARP");
      Book book2 = new Book("WARP");
      if (book1.equals(book2))
         System.out.println("true");
      else
         System.out.println("false");
   }
}