import java.text.*;
public class DiscountBookOrder extends BookOrder{
   private String discountCode;
   private double subtotal, percentOff, total;

   public DiscountBookOrder(String bookCode, int bookQuantity, String keyCode){
      super(bookCode, bookQuantity);
      discountCode = keyCode;
      setPercentOff();
      setTotal();
   }

   public void setPercentOff(){
      if (discountCode.equalsIgnoreCase("a10"))
         percentOff = 0.1;
      else
         percentOff = 0.0;
   }

   public void setTotal(){
      super.setTotal();
      subtotal = super.getTotal();
      total = subtotal - (subtotal * percentOff);
   }

   public double getSubtotal(){ return subtotal; }
   public double getPercentOff(){ return percentOff; }
   public double getTotal(){ return total; }

   public String toString(){
      NumberFormat currency = NumberFormat.getCurrencyInstance();
      NumberFormat percent = NumberFormat.getPercentInstance();
      String message = "Title: " + getBook().getTitle() + "\n"
                     + "Price: " + currency.format(getBook().getPrice()) + "\n"
                     + "Quantity: " + getQuantity() + "\n"
                     + "Subtotal" + currency.format(subtotal) + "\n"
                     + "PercentOff: " + percent.format(percentOff) + "\n"
                     + "Discount Amount: " + currency.format(subtotal - total) +"\n"
                     + "Total: " + currency.format(total) + "\n";
      return message;
   }
}