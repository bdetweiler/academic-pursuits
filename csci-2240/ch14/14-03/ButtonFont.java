import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ButtonFont extends JFrame{
   public ButtonFont(){
      setTitle("Text Example");
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
      Font font = new Font("SansSerif", Font.BOLD, 16);
      JButton addButton = new JButton("Add");
      addButton.setFont(font);
      contentPane.add(addButton);
   }
   public static void main(String[] args){
      ButtonFont frame = new ButtonFont();
      frame.show();
   }
}

