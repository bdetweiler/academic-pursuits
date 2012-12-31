import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class FontsFrame extends JFrame{
   public FontsFrame(){
      setTitle("Fonts and Colors");
      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      int width = 500;
      int height = 175;
      setBounds((int) (d.width-width)/2,
                (int) (d.height-height)/2, width, height);
      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      });
      Container contentPane = getContentPane();
      FontsPanel panel = new FontsPanel();
      contentPane.add(panel);
   }
   public static void main(String[] args){
      FontsFrame frame = new FontsFrame();
      frame.show();
   }
}
class FontsPanel extends JPanel implements ItemListener{
   JComboBox fontComboBox, sizeComboBox, colorComboBox;
   JCheckBox boldCheckBox, italicCheckBox;
   Font font;
   Color color;

   public FontsPanel(){

      GraphicsEnvironment ge;
      ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
      fontComboBox = new JComboBox(ge.getAvailableFontFamilyNames());
      fontComboBox.setSelectedItem("SansSerif");
      fontComboBox.addItemListener(this);

      String[] sizes = {"8", "10", "12", "14", "16", "18", "20"};
      sizeComboBox = new JComboBox(sizes);
      sizeComboBox.setSelectedItem("18");
      sizeComboBox.addItemListener(this);

      String[] colors = {"Black", "Red", "Blue", "Green"};
      colorComboBox = new JComboBox(colors);
      colorComboBox.setSelectedItem("Black");
      colorComboBox.addItemListener(this);

      boldCheckBox = new JCheckBox("Bold");
      boldCheckBox.addItemListener(this);
      italicCheckBox = new JCheckBox("Italic");
      italicCheckBox.addItemListener(this);

      JPanel northPanel = new JPanel();
      northPanel.add(fontComboBox);
      northPanel.add(sizeComboBox);
      northPanel.add(colorComboBox);
      northPanel.add(italicCheckBox);
      northPanel.add(boldCheckBox);

      setLayout(new BorderLayout());
      add(northPanel, BorderLayout.NORTH);
      font = new Font("SansSerif", Font.PLAIN, 18);
   }
public void itemStateChanged(ItemEvent e){
      String fontFamily = (String) fontComboBox.getSelectedItem();
      int style = Font.PLAIN;
      String sizeInt = (String) sizeComboBox.getSelectedItem();
      int size = Integer.parseInt(sizeInt);
      String colorString = (String) colorComboBox.getSelectedItem();
      if (colorString.equals("Black"))
         color = Color.black;
      else if (colorString.equals("Blue"))
         color = Color.blue;
      else if (colorString.equals("Red"))
         color = Color.red;
      else if (colorString.equals("Green"))
         color = Color.green;
      if ((boldCheckBox.isSelected()) && (italicCheckBox.isSelected()))
         style = Font.BOLD + Font.ITALIC;
      else if (boldCheckBox.isSelected())
         style = Font.BOLD;
      else if (italicCheckBox.isSelected())
         style = Font.ITALIC;
      font = new Font(fontFamily, style, size);
      repaint();
   }
   public void paintComponent(Graphics g){
      super.paintComponent(g);
      g.setFont(font);
      g.setColor(color);
      String text = "The quick brown fox jumped over the lazy dog.";
      FontMetrics fm = g.getFontMetrics();
      int widthPanel= getWidth();
      int heightPanel = getHeight();
      int widthString = fm.stringWidth(text);
      int heightString = fm.getHeight();
      g.drawString(text, (widthPanel - widthString)/2,
         (heightPanel-heightString)/2);
   }
}
