import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ShapesFrame extends JFrame{
   public ShapesFrame(){
      setTitle("Shapes Example");
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
      ShapesPanel panel = new ShapesPanel();
      contentPane.add(panel);
   }
   public static void main(String[] args){
      ShapesFrame frame = new ShapesFrame();
      frame.show();
   }
}

class ShapesPanel extends JPanel{
   public void paintComponent(Graphics g){
      super.paintComponent(g);
      g.fillRect(30,30,70,40);
      g.fillRoundRect(120,30,70,40,30,30);
      g.fillOval(210,30,70,40);
      g.fillArc(30,90,70,40,30,120);
      int[] xPoints = {120,155,190};
      int[] yPoints = {130,90,130};
      Polygon triangle = new Polygon(xPoints, yPoints, 3);
      g.fillPolygon(triangle);
      Polygon diamond = new Polygon();
      diamond.addPoint(210,110);
      diamond.addPoint(245,90);
      diamond.addPoint(280,110);
      diamond.addPoint(245,130);
      g.fillPolygon(diamond);


   }
}
