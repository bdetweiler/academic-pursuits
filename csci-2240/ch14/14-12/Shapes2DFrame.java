import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.geom.*;

public class Shapes2DFrame extends JFrame{
   public Shapes2DFrame(){
      setTitle("Shapes2D Example");
      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      int width = 400;
      int height = 200;
      setBounds((int) (d.width-width)/2,
                (int) (d.height-height)/2, width, height);

      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      });
      Container contentPane = getContentPane();
      Shapes2Panel panel = new Shapes2Panel();
      contentPane.add(panel);
   }
   public static void main(String[] args){
      Shapes2DFrame frame = new Shapes2DFrame();
      frame.show();
   }
}

class Shapes2Panel extends JPanel{
   public void paintComponent(Graphics g){
      super.paintComponent(g);

         Graphics2D g2D = (Graphics2D) g;

      Shape line = new Line2D.Double(100,30,30,70);
      Shape rectangle = new Rectangle2D.Double(120,30,70,40);
      Shape roundRectangle = new RoundRectangle2D.Double(210,30,70,40,30,30);
      Shape ellipse = new Ellipse2D.Double(30,90,70,40);
      Shape arc = new Arc2D.Double(120,90,70,40,30,120,Arc2D.CHORD);

      g2D.draw(line);
      g2D.fill(rectangle);
      g2D.draw(roundRectangle);
      g2D.fill(ellipse);
      g2D.draw(arc);

      int[] xPoints = {210,245,280};
      int[] yPoints = {130,90,130};
      Polygon triangle = new Polygon(xPoints, yPoints, 3);
      g2D.fill(triangle);
   }
}
