import java.text.*;

public class BookOrder{
   private Book book;
   private int quantity;
   private double total;

   public BookOrder(){
      this("", 1);
   }
   public BookOrder(String code){
      this(code, 1);
   }
   public BookOrder(String bookCode, int bookQuantity){
      book = new Book(bookCode);
      quantity = bookQuantity;
      setTotal();
   }

   public void setTotal(){
      total = quantity * book.getPrice();
   }

   public void setQuantity(int qty){
      quantity = qty;
   }

   public Book getBook(){ return book; }

   public int getQuantity(){ return quantity; }

   public double getTotal(){ return total; }

   public String toString(){
      NumberFormat currency = NumberFormat.getCurrencyInstance();
      String orderString = "Code: " + book.getCode() + "\n"
                         + "Title: " + book.getTitle() + "\n"
                         + "Price: " + currency.format(book.getPrice()) + "\n"
                         + "Quantity: " + quantity + "\n"
                         + "Total: " + currency.format(total) + "\n";
      return orderString;
   }

   public boolean equals(Object object){
      if (object instanceof BookOrder){
         BookOrder order2 = (BookOrder) object;
         if (
            book.equals(order2.getBook()) &&
            quantity == order2.getQuantity() &&
            total == order2.getTotal()
            )
            return true;
       }
       return false;
   }
}