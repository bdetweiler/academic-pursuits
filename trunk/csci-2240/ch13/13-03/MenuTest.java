//To see practical example of menus, view the BookFrame class in the
//BookMaintenance folder located in Book_Programs/ch13
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class MenuTest extends JFrame{
   private JMenuItem exitMenuItem, addMenuItem, updateMenuItem,
                  deleteMenuItem, moveMenuItem;

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
      exitMenuItem = new JMenuItem("Exit");
      fileMenu.add(exitMenuItem);

      JMenu recordsMenu = new JMenu("Records");
      addMenuItem = new JMenuItem("Add");
      updateMenuItem = new JMenuItem("Update");
      deleteMenuItem = new JMenuItem("Delete");
      moveMenuItem = new JMenuItem("Move");
      recordsMenu.add(addMenuItem);
      recordsMenu.add(updateMenuItem);
      recordsMenu.add(deleteMenuItem);
      recordsMenu.addSeparator();
      recordsMenu.add(moveMenuItem);
      updateMenuItem.setEnabled(false);

      JMenuBar menuBar = new JMenuBar();
      menuBar.add(fileMenu);
      menuBar.add(recordsMenu);

      setJMenuBar(menuBar);
   }

   public static void main(String[] args){
      JFrame frame = new MenuTest();
      frame.show();
   }
}
