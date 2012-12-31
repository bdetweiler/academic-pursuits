import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class CheckBoxTest extends JFrame{

   private JCheckBox taxCheckBox;

   public CheckBoxTest(){
      setTitle("Check Box Test");
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

      Container contentPane = getContentPane();
      taxCheckBox = new JCheckBox("Include sales tax", true);
      contentPane.add(taxCheckBox);
   }

   public static void main(String[] args){
      JFrame frame = new CheckBoxTest();
      frame.show();
   }
}



