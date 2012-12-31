//the purpose of this application is to show you how the focus listener
//can be used for data validation. As soon as focus leaves the quantity
//text field, Java checks that a valid quantity was entered. If not,
//it handles is appropriately in the focusLost method.
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class FocusTest extends JFrame implements FocusListener, ActionListener{
   private JLabel quantityLabel, validLabel;
   private JTextField quantityTextField, validTextField;
   private JButton calculateButton;

   public FocusTest(){
      setTitle("Focus Test");
      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      int height = d.height;
      int width = d.width;
      setBounds(width/4, height/4, 200, 200);
      setResizable(false);

      addWindowListener(new WindowAdapter(){
           public void windowClosing(WindowEvent e){
               System.exit(0);
            }
     });
      Container contentPane = getContentPane();
      JPanel displayPanel = new JPanel();

      quantityLabel = new JLabel("Quantity");
      validLabel = new JLabel("Validity");
     quantityTextField = new JTextField(10);
     validTextField = new JTextField(10);
     validTextField.setEditable(false);
     calculateButton = new JButton("Calculate");
      calculateButton.addActionListener(this);

      quantityTextField.addFocusListener(this);

      displayPanel.add(quantityLabel);
      displayPanel.add(quantityTextField);
      displayPanel.add(validLabel);
      displayPanel.add(validTextField);
      displayPanel.add(calculateButton);

      contentPane.add(displayPanel);
    }

   public void focusLost(FocusEvent e){
       if (e.getComponent() == quantityTextField && !e.isTemporary()){
         try{
           int quantity = Integer.parseInt(quantityTextField.getText());
         }
         catch(NumberFormatException nfe){
          validTextField.setText("Invalid quantity");
            JOptionPane.showMessageDialog(null, "Invalid quantity.\n"
            + "Please enter a positive number.",
            "Error", JOptionPane.ERROR_MESSAGE);
            quantityTextField.requestFocusInWindow();
         }
      }
    }

    public void focusGained(FocusEvent e){
    }

   public void actionPerformed(ActionEvent e){
      Object source = e.getSource();
      if (source == calculateButton){
         validTextField.setText("Valid quantity");
      }
   }

   public static void main(String[] args){
     JFrame frame = new FocusTest();
     frame.show();
   }
}

