import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class TextFrame extends JFrame{
   public TextFrame(){
      setTitle("Text Example");
      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      setBounds((int) (d.width-330)/2, (int) (d.height-165)/2, 330, 165);
      int width = 500;
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
      TextFrame frame = new TextFrame();
      frame.show();
   }
}

class TextPanel extends JPanel{
   public void paintComponent(Graphics g){
      super.paintComponent(g);
      Font f = new Font("SansSerif", Font.BOLD + Font.ITALIC, 16);
      g.setFont(f);
      String text = "The quick brown fox jumped over the lazy dog.";
      FontMetrics fm = g.getFontMetrics();
      int widthString = fm.stringWidth(text);
      int heightString = fm.getHeight();
      int widthPanel= this.getWidth();
      int heightPanel = this.getHeight();
      g.drawString(text, (widthPanel - widthString) / 2,
                         (heightPanel - heightString) / 2);
   }
}
