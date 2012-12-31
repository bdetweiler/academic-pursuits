//the purpose of this application is to show that if you enter the quantity,
//you can just press Alt+C to compute the total...of course, it's a trivial
//application. Check out the BookOrderList and BookMaintenance application in
//Book_Programs/ch12 for practical examples that uses key listeners.
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class KeyListenerTest extends JFrame implements KeyListener, ActionListener{
   private JLabel quantityLabel, totalLabel;
   private JTextField quantityTextField, totalTextField;
   private JButton calculateButton;

   public KeyListenerTest(){
      setTitle("Key Listener Test");
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
      totalLabel = new JLabel("Total");
      quantityTextField = new JTextField(10);
      totalTextField = new JTextField(10);
      totalTextField.setEditable(false);
      calculateButton = new JButton("Calculate");
      calculateButton.addActionListener(this);

      quantityTextField.addKeyListener(this);

      displayPanel.add(quantityLabel);
      displayPanel.add(quantityTextField);
      displayPanel.add(totalLabel);
      displayPanel.add(totalTextField);
      displayPanel.add(calculateButton);

      contentPane.add(displayPanel);
    }

   public void keyPressed(KeyEvent e){
         int keyCode = e.getKeyCode();
         if ((keyCode == KeyEvent.VK_C) && (e.isAltDown())){
            calculateButton.requestFocusInWindow();
            calculateButton.doClick();
         }
   }
   public void keyReleased(KeyEvent e){
   }
   public void keyTyped(KeyEvent e){
   }

   public void actionPerformed(ActionEvent e){
      Object source = e.getSource();
      if (source == calculateButton){
         totalTextField.setText("Quantity is " + quantityTextField.getText());
      }
   }

   public static void main(String[] args){
     JFrame frame = new KeyListenerTest();
     frame.show();
   }
}

