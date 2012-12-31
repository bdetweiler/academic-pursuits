
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
import javax.swing.event.*;

public class ScrollPaneTest extends JFrame implements ListSelectionListener{
   private JList titleList;
   public ScrollPaneTest(){
      setTitle("Scroll Pane Test");
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
      titleList = new JList(titles);
      titleList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
      titleList.addListSelectionListener(this);
      titleList.setVisibleRowCount(4);
      JScrollPane titleScroll = new JScrollPane(titleList);
      titlePanel.add(titleScroll);

      contentPane.add(titlePanel);
   }

   public void valueChanged(ListSelectionEvent e){
      Object source = e.getSource();
      if ((source == titleList)&&(e.getValueIsAdjusting() == false)){
          int recordNumber = titleList.getSelectedIndex();
          JOptionPane.showMessageDialog(null, "You selected item number "
                                         + (recordNumber+1));
      }
   }

   public static void main(String[] args){
      JFrame frame = new ScrollPaneTest();
      frame.show();
   }
}

