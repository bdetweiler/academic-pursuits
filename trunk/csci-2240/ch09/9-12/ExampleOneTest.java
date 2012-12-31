import javax.swing.JOptionPane;
public class ExampleOneTest{
   public static void main(String[] args){
      String inputString = JOptionPane.showInputDialog(
         "Enter your full name: ");
      String name = inputString.trim();
      int indexOfSpace = name.indexOf(" ");
      String firstName = null;
      if (indexOfSpace == -1)
         firstName = name.substring(0);
      else
         firstName = name.substring(0, indexOfSpace);
      System.out.println(firstName);
      System.exit(0);
   }
}
