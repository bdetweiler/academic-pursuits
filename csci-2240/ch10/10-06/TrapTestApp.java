import javax.swing.*;

public class TrapTestApp{
   public static void main(String[] args){
      String name = JOptionPane.showInputDialog("Enter your full name: ");
      String firstName = getFirstName(name);
      JOptionPane.showMessageDialog(null, "First name: " + firstName,
         "Trap Test", JOptionPane.PLAIN_MESSAGE);
      System.exit(0);
   }

   public static String getFirstName(String inputName){
      String name = inputName.trim();
      int indexOfSpace = name.indexOf(" ");
      String firstName = null;
      if (indexOfSpace == -1)
         firstName = name;
      else
         firstName = name.substring(0, indexOfSpace);
      return firstName;
   }
}
