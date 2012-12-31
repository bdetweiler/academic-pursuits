import javax.swing.JOptionPane;
import java.text.*;

public class EnhancedInvoiceApp{
   public static void main(String[] args){
      String choice = "";
      while (!(choice.equalsIgnoreCase("x"))){
         String inputString = JOptionPane.showInputDialog(null,
            "Enter order total: ", "Invoice", JOptionPane.PLAIN_MESSAGE);
         double orderTotal = parseTotal(inputString);
         double discountAmount = 0;
         if (orderTotal >= 100)
            discountAmount = orderTotal * .2;
         else
            discountAmount = orderTotal * .1;
         double invoiceTotal = orderTotal - discountAmount;
         NumberFormat currency = NumberFormat.getCurrencyInstance();
         String message = "Order total: " + currency.format(orderTotal) + "\n"
            + "Discount amount: " + currency.format(discountAmount) + "\n"
            + "Invoice total: " + currency.format(invoiceTotal) + "\n\n"
            + "To continue, press Enter.\n"
            + "To exit, enter 'x': ";
         choice = JOptionPane.showInputDialog(null,
            message, "Invoice", JOptionPane.PLAIN_MESSAGE);
      }
      System.exit(0);
   }

   private static double parseTotal(String totalString){
      double orderTotal = 0;
      boolean tryAgain = true;
      while(tryAgain){
         try{
            orderTotal = Double.parseDouble(totalString);
            while (orderTotal <= 0){
               totalString = JOptionPane.showInputDialog(null,
                    "Invalid order total. \n"
                  + "Please enter a positive number: ",
                  "Invoice", JOptionPane.ERROR_MESSAGE);
               orderTotal = Double.parseDouble(totalString);
            }
            tryAgain = false;
         }
         catch(NumberFormatException e){
            totalString = JOptionPane.showInputDialog(null,
                 "Invalid order total. \n"
               + "Please enter a number: ",
             "Invoice", JOptionPane.ERROR_MESSAGE);
         }
      }
      return orderTotal;
   }
}