import java.text.*;

public class BookOrder{
   private Book book;
   private int quantity;
   private double total;

   public BookOrder(String bookCode, int bookQuantity){
      book = new Book(bookCode);
      quantity = bookQuantity;
      setTotal();
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

   public static void main(String[] args){
		 BookOrder bookOrder1 = new BookOrder("MBDK", 3);
	     System.out.println("CONSTRUCTOR 1: \n" + bookOrder1);

	     System.out.println("SET METHODS");
	     System.out.println("setTotal method calculates total");
	     System.out.println();

	     System.out.println("GET METHODS");
	     System.out.print("getBook method returns: \n"
	         + bookOrder1.getBook());
	     System.out.println("\ngetQuantity method returns: "
	         + bookOrder1.getQuantity());
	     System.out.println("getTotal method returns: "
	         + bookOrder1.getTotal());
	  }
}