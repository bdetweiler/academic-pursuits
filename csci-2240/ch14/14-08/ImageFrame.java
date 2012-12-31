import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ImageFrame extends JFrame{
   public ImageFrame(){
      setTitle("Book Invoice System");
      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      int width = 400;
      int height = 175;
      setBounds((int) (d.width-width)/2,
                (int) (d.height-height)/2, width, height);
      setResizable(false);

      ImageIcon murachIconImage = new ImageIcon("MurachIcon.gif");
      Image murachIcon = murachIconImage.getImage();
      setIconImage(murachIcon);

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

   public ImagePanel(){

      ImageIcon buttonIcon = new ImageIcon("MurachIcon.gif");
      JButton createOrdersButton = new JButton("Create Book Orders");
      createOrdersButton.setIcon(buttonIcon);

      JButton maintainBooksButton = new JButton("Maintain Books");
      maintainBooksButton.setIcon(buttonIcon);

      JPanel buttonPanel = new JPanel();
      buttonPanel.add(maintainBooksButton);
      buttonPanel.add(createOrdersButton);
      buttonPanel.setBackground(Color.red);

      setLayout(new BorderLayout());
      add(buttonPanel, BorderLayout.SOUTH);

   }

   public void paintComponent(Graphics g){
      super.paintComponent(g);
      setBackground(Color.red);
      ImageIcon murachLogoImageIcon = new ImageIcon("MurachLogo.gif");
      Image murachLogo = murachLogoImageIcon.getImage();
      g.drawImage(murachLogo, 110, 10, this);
   }
}
