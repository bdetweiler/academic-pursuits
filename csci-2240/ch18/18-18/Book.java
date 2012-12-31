import java.io.*;

public class Book{
   private String code;
   private String title;
   private double price;

   public Book(String bookCode, String bookTitle, double bookPrice){
      code = bookCode;
      title = bookTitle;
      price = bookPrice;
   }
   public Book(String bookCode) throws IOException{
      code = bookCode;
      Book tempBook = BookIO.readRecord(bookCode);
      title = tempBook.getTitle();
      price = tempBook.getPrice();
   }

   public String getCode(){ return code; }
   public String getTitle(){ return title; }
   public double getPrice(){ return price; }
}
