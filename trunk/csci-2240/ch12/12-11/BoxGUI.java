import javax.swing.*;
import java.awt.event.*; //WindowListener
import java.awt.*;       //for Toolkit
import java.text.*;
import javax.swing.border.*;


public class BoxGUI extends JFrame{
   public BoxGUI(){
     setTitle("Box Layout");


     Toolkit tk = Toolkit.getDefaultToolkit();
     Dimension d = tk.getScreenSize();
     int height = d.height;
     int width = d.width;
     setBounds(width/4, height/4, 250, 220);
     setResizable(true);
     addWindowListener(new WindowAdapter(){
        public void windowClosing(WindowEvent e){
           System.exit(0);
        }
     });

      Container contentPane = getContentPane();
     JPanel panel = new JPanel();
     panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
     JLabel one = new JLabel("First");
     JTextField two = new JTextField("Second");
     JLabel three = new JLabel("Third");
     JTextField four = new JTextField("Fourth");
     JCheckBox five = new JCheckBox("Fifth", true);
     JButton six = new JButton("Sixth");
     JButton seven = new JButton("Seventh");
     JButton eight = new JButton("Eighth");
     panel.add(one);
     panel.add(two);
     panel.add(three);
     panel.add(four);
     panel.add(five);
     panel.add(six);
     panel.add(seven);
     panel.add(eight);
     contentPane.add(panel);
     }
     public static void main(String[] args){
        JFrame frame = new BoxGUI();
        frame.show();
     }

}