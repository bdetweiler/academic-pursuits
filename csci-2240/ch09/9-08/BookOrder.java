import java.text.*;

public class BookOrder implements Comparable{
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
   public int compareTo(Object o){
      BookOrder bookOrder2 = (BookOrder) o;
      double total1 = this.getTotal();
      double total2 = bookOrder2.getTotal();
      if (total1 < total2)
         return -1;
      if (total1 > total2)
         return 1;
      return 0;
   }

   public void setTotal(){
      total = quantity * book.getPrice();
   }

   public Book getBook(){
      return book;
   }

   public int getQuantity(){
      return quantity;
   }

   public double getTotal(){
      return total;
   }

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