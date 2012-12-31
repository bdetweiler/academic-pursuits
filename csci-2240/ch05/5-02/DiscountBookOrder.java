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
      subtotal = super.getQuantity() * super.getBook().getPrice();
      total = subtotal - (subtotal * percentOff);
   }

   public double getSubtotal(){ return subtotal; }
   public double getPercentOff(){ return percentOff; }
   public double getTotal(){ return total; }
}
