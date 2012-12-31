import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class FirstTextFieldGUI extends JFrame{

   public FirstTextFieldGUI(){
      setTitle("Adding text fields");
      setBounds(267, 200, 300, 90);
      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      });
      JPanel panel = new JPanel();
      JTextField oneTextField = new JTextField("Test: ", 20);
      JTextField twoTextField = new JTextField(10);
      panel.add(oneTextField);
      panel.add(twoTextField);
      Container contentPane = getContentPane();
      contentPane.add(panel);
   }

   public static void main(String[] args){
      JFrame frame = new FirstTextFieldGUI();
      frame.show();
   }
}

