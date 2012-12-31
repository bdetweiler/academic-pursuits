import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class BorderTest extends JFrame{
   public BorderTest(){
      setTitle("Border Test");
      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      int height = d.height;
      int width = d.width;
      setBounds(width/3, height/3, width/3, height/3);
      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      });
      Container contentPane = getContentPane();
      contentPane.add(new JButton("North"), "North");
      contentPane.add(new JButton("South"), "South");
      contentPane.add(new JButton("East"), "East");
      contentPane.add(new JButton("West"), "West");
      contentPane.add(new JButton("Center"), "Center");
   }
   public static void main(String[] args){
      JFrame frame = new BorderTest();
      frame.show();
   }
}
