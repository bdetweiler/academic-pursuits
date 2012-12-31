import javax.swing.JOptionPane;

public class TryTestApp{
	public static void main(String[] args){

		String inputString = JOptionPane.showInputDialog("Enter order total: ");
		double orderTotal = 0;
		try{
   			orderTotal = Double.parseDouble(inputString);
		}
		catch(NumberFormatException e){
   			inputString = JOptionPane.showInputDialog(
      					"Invalid order total. \n"
    					+ "Please enter a number: ");
   			orderTotal = Double.parseDouble(inputString);
		}
		System.exit(0);
	}
}
