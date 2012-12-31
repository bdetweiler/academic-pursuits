import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ColorFrame extends JFrame{
   public ColorFrame(){
      setTitle("Color Example");
      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      setBounds((int) (d.width-330)/2, (int) (d.height-165)/2, 330, 165);
      int width = 200;
      int height = 165;
      setBounds((int) (d.width-width)/2,
                (int) (d.height-height)/2, width, height);

      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      });
      Container contentPane = getContentPane();
      TextPanel panel = new TextPanel();
      contentPane.add(panel);
   }
   public static void main(String[] args){
      ColorFrame frame = new ColorFrame();
      frame.show();
   }
}

class TextPanel extends JPanel{
   public void paintComponent(Graphics g){
      super.paintComponent(g);
      g.setColor(Color.red);
      g.drawString("This text is red!", 30, 30);
      g.setColor(Color.blue);
      g.drawString("This text is blue!", 30, 70);
   }
}
