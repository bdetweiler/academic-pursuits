import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

public class RadioButtonTest extends JFrame implements ActionListener{

   private JRadioButton paymentRadioButton, amountRadioButton;

   public RadioButtonTest(){
      setTitle("Radio Button Test");
      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      int width = 267;
      int height = 250;
      setBounds((d.width - width)/2, (d.height - height)/2, width, height);
      setResizable(false);
      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      });

      JPanel radioPanel = new JPanel();
      paymentRadioButton = new JRadioButton("Monthly Payment");
      amountRadioButton = new JRadioButton("Loan Amount", true);
      paymentRadioButton.addActionListener(this);
      amountRadioButton.addActionListener(this);

      ButtonGroup radioGroup = new ButtonGroup();
      radioGroup.add(paymentRadioButton);
      radioGroup.add(amountRadioButton);

      radioPanel.add(paymentRadioButton);
      radioPanel.add(amountRadioButton);
      Border titledRadioBorder =
         BorderFactory.createTitledBorder("Calculate");
      radioPanel.setBorder(titledRadioBorder);

      Container contentPane = getContentPane();
      contentPane.add(radioPanel);

   }
    public void actionPerformed(ActionEvent e){
      if(paymentRadioButton.isSelected()){
         JOptionPane.showMessageDialog(null, "Payment radio button selected.");
      }
      else if(amountRadioButton.isSelected()){
         JOptionPane.showMessageDialog(null, "Amount radio button selected.");
      }
   }
   public static void main(String[] args){
      JFrame frame = new RadioButtonTest();
      frame.show();
   }
}



