//To see practical example of menus, view the BookFrame class in the
//BookMaintenance folder located in Book_Programs/ch13
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class MenuTest extends JFrame{
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
      exitMenuItem = new JMenuItem("Exit");
      fileMenu.add(exitMenuItem);

      JMenu recordsMenu = new JMenu("Records");
      addMenuItem = new JMenuItem("Add");
      updateMenuItem = new JMenuItem("Update");
      deleteMenuItem = new JMenuItem("Delete");
      recordsMenu.add(addMenuItem);
      recordsMenu.add(updateMenuItem);
      recordsMenu.add(deleteMenuItem);
      recordsMenu.addSeparator();

      JMenu moveMenu = new JMenu("Move");
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

   public static void main(String[] args){
      JFrame frame = new MenuTest();
      frame.show();
   }
}
