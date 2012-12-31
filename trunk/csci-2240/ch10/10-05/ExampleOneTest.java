import javax.swing.JOptionPane;

public class ExampleOneTest{
   public static void main(String[] args){
      String inputQuantity = JOptionPane.showInputDialog(
                       "Enter a quantity:");
      int quantity = 0;
      boolean tryAgain = true;
      while(tryAgain){
            try{
               quantity = Integer.parseInt(inputQuantity);
               tryAgain = false;
            }
            catch(NumberFormatException e){
               inputQuantity = JOptionPane.showInputDialog(
               "Invalid quantity. \n"
               + "Please enter a number.");
            }
      }
      System.exit(0);
   }
}
