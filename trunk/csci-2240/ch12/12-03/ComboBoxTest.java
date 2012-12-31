//To see a working application that uses a combo box, you can view
//the classes in the BookPrograms\ch12\ComboBookOrder folder.
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class ComboBoxTest extends JFrame implements ItemListener{
   private JComboBox titleComboBox;
   public ComboBoxTest(){
      setTitle("Combo Box Test");
      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      int height = d.height;
      int width = d.width;
      setBounds(width/4, height/4, 350, 200);
      setResizable(false);

      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      });
      Container contentPane = getContentPane();
      JPanel titlePanel = new JPanel();

      String[] titles = {"War and Peace", "Moby Dick",
                         "Wuthering Heights", "Catcher in the Rye",
                         "Old Yeller", "Romeo and Juliet"};
      titleComboBox = new JComboBox(titles);
      titleComboBox.addItemListener(this);
      titlePanel.add(titleComboBox);

      contentPane.add(titlePanel);
   }

   public void itemStateChanged(ItemEvent e){
      Object source = e.getSource();
      if ((source == titleComboBox)&&(e.getStateChange() == ItemEvent.SELECTED)){
         int recordNumber = titleComboBox.getSelectedIndex();
         JOptionPane.showMessageDialog(null, "You selected item number "
                                             + (recordNumber+1));
      }
   }
   public static void main(String[] args){
      JFrame frame = new ComboBoxTest();
      frame.show();
   }
}

