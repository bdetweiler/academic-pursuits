import java.text.*;

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
      else
         title = "Not Found";
   }

   public void setPrice(String bookCode){
      if (bookCode.equalsIgnoreCase("WARP"))
         price = 14.95;
      else
         price = 11.95;
   }

   public String getCode(){ return code; }
   public String getTitle(){ return title; }
   public double getPrice(){ return price; }

   public String toString(){
      NumberFormat currency = NumberFormat.getCurrencyInstance();
      String orderString = "Code: " + code + "\n"
                         + "Title: " + title + "\n"
                         + "Price: " + currency.format(price) + "\n";
      return orderString;
   }

   public boolean equals(Object object){
      if (object instanceof Book){
         Book book2 = (Book) object;
         if (
            code.equals(book2.getCode()) &&
            title.equals(book2.getTitle()) &&
            price == book2.getPrice()
            )
            return true;
      }
      return false;
   }
}