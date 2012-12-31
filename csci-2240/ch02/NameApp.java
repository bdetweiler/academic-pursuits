import javax.swing.JOptionPane;

public class NameApp
{
     public static void main(String[] args)
     {
          String inputString = JOptionPane.showInputDialog(
               "Enter your first name: ");
          String message = "First name: " + inputString + "\n\n" 
               + "Press the Enter key to exit.";
          JOptionPane.showInputDialog(message);
          System.exit(0);
     }
}
               
               

          
