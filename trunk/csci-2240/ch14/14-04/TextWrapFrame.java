import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Vector;

public class TextWrapFrame extends JFrame{
   public TextWrapFrame(){
      setTitle("Text Wrap Example");
      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      setBounds((int) (d.width-330)/2, (int) (d.height-165)/2, 330, 165);
      int width = 235;
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
      TextWrapFrame frame = new TextWrapFrame();
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
      int widthLine = widthPanel - 20;
      Vector strings = new Vector();
      String tempString = "";
      int maxLineWidth = 0;
      for (int i = 0; i < text.length(); i++){
         tempString += text.charAt(i);
         maxLineWidth += fm.charWidth(text.charAt(i));
         if ((maxLineWidth >= widthLine) || (i==text.length() - 1)){
            strings.add(tempString);
            maxLineWidth = 0;
            tempString = "";
         }
      }
      int lines = strings.size();
      int y = (heightPanel - (heightString * lines)) / 2;
      for (int i = 0; i < lines; i++){
         String line = (String) strings.get(i);
         g.drawString(line, 10, y + i * heightString);
      }
   }
}
