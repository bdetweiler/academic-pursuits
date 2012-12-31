import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ImageFrame extends JFrame{
   public ImageFrame(){
      setTitle("Image Example");
      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      int width = 400;
      int height = 175;
      setBounds((int) (d.width-width)/2,
                (int) (d.height-height)/2, width, height);
      setResizable(false);
      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      });
      Container contentPane = getContentPane();
      ImagePanel panel = new ImagePanel();
      contentPane.add(panel);
   }

   public static void main(String[] args){
      ImageFrame frame = new ImageFrame();
      frame.show();
   }
}

class ImagePanel extends JPanel{

   public ImagePanel(){}

   public void paintComponent(Graphics g){
      super.paintComponent(g);
      Graphics2D g2D = (Graphics2D) g;
      Toolkit tk = Toolkit.getDefaultToolkit();
      Image murachLogo = tk.getImage("MurachLogo.gif");
      g2D.drawImage(murachLogo, 110, 10, this);
   }
}