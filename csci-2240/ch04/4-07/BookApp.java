import javax.swing.JOptionPane;

public class BookApp{
   public static void main(String args[]){
      String choice = "";
      while (!(choice.equalsIgnoreCase("x"))){
         String code = JOptionPane.showInputDialog(
            "Enter a book code:");
         Book book = new Book(code);
         String message = "You have selected:\n"
                        + "   Title: " + book.getTitle() + "\n"
                        + "   Price: " + book.getPrice() + "\n\n"
                        + "Press Enter to continue or enter 'x' to exit:";
         choice = JOptionPane.showInputDialog(null,
            message, "Book", JOptionPane.PLAIN_MESSAGE);
      }//end while
      System.exit(0);
   }
}
