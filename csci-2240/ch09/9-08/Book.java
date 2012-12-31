public class Book{
   private String code;
   private String title;
   private double price;

   public Book(String bookCode){
      code = bookCode;
      setTitle(bookCode);
      setPrice(bookCode);
   }

   public void setTitle(String bookCode){
      if (bookCode.equalsIgnoreCase("WARP"))
         title = "War and Peace";
      else if (bookCode.equalsIgnoreCase("MBDK"))
         title = "Moby Dick";
      else if (bookCode.equalsIgnoreCase("CITR"))
         title = "Catcher in the Rye";
      else
         title = "Not Found";
   }


   public void setPrice(String bookCode){
      if (bookCode.equalsIgnoreCase("WARP"))
         price = 14.95;
      else if (bookCode.equalsIgnoreCase("MBDK"))
         price = 12.95;
      else if (bookCode.equalsIgnoreCase("CITR"))
         price = 9.95;
      else
         price = 0.0;
   }

   public String getCode(){
      return code;
   }

   public String getTitle(){
      return title;
   }

   public double getPrice(){
      return price;
   }

}