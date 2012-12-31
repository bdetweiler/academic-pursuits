//To see practical example of menus, view the BookFrame class in the
//BookMaintenance folder located in Book_Programs/ch13
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class MenuTest extends JFrame implements ActionListener{
   private JMenuItem exitMenuItem, addMenuItem, updateMenuItem,
                  deleteMenuItem, moveMenuItem;
   private JMenuItem firstMenuItem, prevMenuItem, nextMenuItem, lastMenuItem;

   public MenuTest(){
      setTitle("Menu Test");
      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      int width = 267;
      int height = 250;
      setBounds((d.width - width)/2, (d.height - height)/2, width, height);
      setResizable(false);
      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      });

      JMenu fileMenu = new JMenu("File");
      fileMenu.setMnemonic('F');
      JMenuItem exitMenuItem = new JMenuItem("Exit", 'x');
      fileMenu.add(exitMenuItem);

      JMenu recordsMenu = new JMenu("Records");
      recordsMenu.setMnemonic('R');

      addMenuItem = new JMenuItem("Add", 'A');
      addMenuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_A,
         Event.CTRL_MASK + Event.ALT_MASK));

      updateMenuItem = new JMenuItem("Update", 'U');
      updateMenuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_U,
         Event.CTRL_MASK));

      deleteMenuItem = new JMenuItem("Delete", 'D');
      deleteMenuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_D,
         Event.CTRL_MASK));

      recordsMenu.add(addMenuItem);
      recordsMenu.add(updateMenuItem);
      recordsMenu.add(deleteMenuItem);
      recordsMenu.addSeparator();

      exitMenuItem.addActionListener(this);
      addMenuItem.addActionListener(this);
      updateMenuItem.addActionListener(this);
      deleteMenuItem.addActionListener(this);

      JMenu moveMenu = new JMenu("Move");
      moveMenu.setMnemonic('M');
      firstMenuItem = new JMenuItem("First");
      prevMenuItem = new JMenuItem("Prev");
      nextMenuItem = new JMenuItem("Next");
      lastMenuItem = new JMenuItem("Last");
      moveMenu.add(firstMenuItem);
      moveMenu.add(prevMenuItem);
      moveMenu.add(nextMenuItem);
      moveMenu.add(lastMenuItem);

      recordsMenu.add(moveMenu);

      updateMenuItem.setEnabled(false);

      JMenuBar menuBar = new JMenuBar();
      menuBar.add(fileMenu);
      menuBar.add(recordsMenu);

      setJMenuBar(menuBar);
   }
    public void actionPerformed(ActionEvent e){
            Object source = e.getSource();
            if (source instanceof JMenuItem){
               JMenuItem item = (JMenuItem) source;
               String text = item.getText();
               if (text.equals("Exit"))
                  System.exit(0);
               if (text.equals("Add"))
                  JOptionPane.showMessageDialog(null, "You selected the Add menu item.");
               if (text.equals("Update"))
                  JOptionPane.showMessageDialog(null, "You selected the Update menu item.");
               if (text.equals("Delete"))
               JOptionPane.showMessageDialog(null, "You selected the Delete menu item.");
            }
   }
   public static void main(String[] args){
      JFrame frame = new MenuTest();
      frame.show();
   }
}
