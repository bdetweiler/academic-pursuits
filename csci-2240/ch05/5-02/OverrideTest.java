import javax.swing.JOptionPane;
import java.text.*;

public class OverrideTest{
   public static void main(String[] args){
      NumberFormat currency = NumberFormat.getCurrencyInstance();
      NumberFormat percent = NumberFormat.getPercentInstance();
      DiscountBookOrder order = new DiscountBookOrder("WARP", 2, "a10");
      String test = "Title: " + order.getBook().getTitle() + "\n"
         + "Price: " + order.getBook().getPrice() + "\n"
         + "Quantity: " + order.getQuantity() + "\n"
         + "Subtotal: " + currency.format(order.getSubtotal()) + "\n"
         + "PercentOff: " + percent.format(order.getPercentOff()) + "\n"
         + "Total: " + currency.format(order.getTotal());
      JOptionPane.showMessageDialog(null, test);
      System.exit(0);
   }
}
