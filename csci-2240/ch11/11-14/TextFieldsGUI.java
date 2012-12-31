import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class TextFieldsGUI extends JFrame{
   private JLabel amountLabel, rateLabel, yearsLabel, paymentLabel;

   public TextFieldsGUI(){
      setTitle("Working with text fields");
      setBounds(267, 200, 300, 90);
      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      });

      JPanel panel = new JPanel();
      JTextField oneTextField = new JTextField("Test", 20);
      JTextField twoTextField = new JTextField(10);
      panel.add(oneTextField);
      panel.add(twoTextField);

      String data = oneTextField.getText();
      twoTextField.setText(data);
      twoTextField.setColumns(20);
      twoTextField.setEditable(false);

      Container contentPane = getContentPane();
      contentPane.add(panel);
   }

   public static void main(String[] args){
      JFrame frame = new TextFieldsGUI();
      frame.show();
   }

}