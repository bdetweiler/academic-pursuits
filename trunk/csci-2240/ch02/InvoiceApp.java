import javax.swing.*;

public class InvoiceApp
{
     public static void main(String[] args)
     {
          String choice = "";
          while(!(choice.equalsIgnoreCase("x")))
          {
               String inputString = JOptionPane.showInputDialog(
                    "Enter order total: ");
               double orderTotal = Double.parseDouble(inputString);
               double discountAmount = 0;
               if (orderTotal >= 100)
                    discountAmount = orderTotal * .2;
               else
                    discountAmount = orderTotal * .1;
               double invoiceTotal = orderTotal - discountAmount;
               String message = "Order total: " + orderTotal + "\n"
                              + "Discount amount: " + discountAmount + "\n"
                              + "Invoice total: " + invoiceTotal + "\n\n"
                              + "To continue, press Enter.\n"
                              + "To exit, enter 'x': ";
               choice = JOptionPane.showInputDialog(message);
          }
          System.exit(0);    
     } // end while loop
     
}
