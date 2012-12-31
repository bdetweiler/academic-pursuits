import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class OneLabelGUI extends JFrame{

   public OneLabelGUI(){
      setTitle("Adding a label");
      setBounds(267, 200, 200, 150);
      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      });
      Container contentPane = getContentPane();
      JPanel panel = new JPanel();
      JLabel label = new JLabel("Label One");
      panel.add(label);
      contentPane.add(panel);
   }

   public static void main(String[] args){
      JFrame frame = new OneLabelGUI();
      frame.show();
   }
}

