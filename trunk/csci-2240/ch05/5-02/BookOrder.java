import java.text.*;

public class BookOrder{
   private Book book;
   private int quantity;
   private double total;

   private static int orderObjectCount = 0;

   public BookOrder(String bookCode, int bookQuantity){
      book = new Book(bookCode);
      quantity = bookQuantity;
      setTotal();
      orderObjectCount++;
   }

   public void setTotal(){
      total = quantity * book.getPrice();
   }

   public double getTotal(){ return total; }

   public Book getBook(){ return book; }

   public int getQuantity() { return quantity; }

   public String toString(){
      NumberFormat currency = NumberFormat.getCurrencyInstance();
      String orderString = "Code: " + book.getCode() + "\n"
                         + "Title: " + book.getTitle() + "\n"
                         + "Price: " + currency.format(book.getPrice()) + "\n"
                         + "Quantity: " + quantity + "\n"
                         + "Total: " + currency.format(total) + "\n";
      return orderString;
   }
   public static int getOrderObjectCount(){
      return orderObjectCount;
   }

}