import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class FlowTest extends JFrame{
   public FlowTest(){
      setTitle("Flow Layout");
      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      int height = d.height;
      int width = d.width;
      setBounds(width/3, height/3, width/2, height/4);
      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      });
      Container contentPane = getContentPane();
      JPanel panel = new JPanel();
      panel.add(new JButton("Button One"));
      panel.add(new JButton("Button Two"));
      panel.add(new JButton("Button Three"));
      panel.add(new JButton("Button Four"));
      panel.add(new JButton("Button Five"));
      contentPane.add(panel);
   }
   public static void main(String[] args){
      JFrame frame = new FlowTest();
      frame.show();
   }
}
