//If you select the resizable check box, you can change the size of the frame.
//To see practical example of menus, view the LoanCalculatorFrame class in the
//LoanCalculator folder located in Book_Programs/ch13

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class CheckBoxMenuTest extends JFrame implements ActionListener{
    private JCheckBoxMenuItem resizableItem;

   public CheckBoxMenuTest(){
      setTitle("Check Box Menu Item Test");
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

      JMenu calculateMenu = new JMenu("Calculate");
      calculateMenu.setMnemonic('C');

      JMenu windowMenu = new JMenu("Window");
      windowMenu.setMnemonic('W');
      resizableItem = new JCheckBoxMenuItem("Resizable", false);
      windowMenu.add(resizableItem);

      resizableItem.addActionListener(this);
        exitMenuItem.addActionListener(this);

      JMenuBar menuBar = new JMenuBar();
      menuBar.add(fileMenu);
      menuBar.add(calculateMenu);
      menuBar.add(windowMenu);

      setJMenuBar(menuBar);

   }

   public void actionPerformed(ActionEvent e){
      Object source = e.getSource();
      if (source instanceof JMenuItem){
         String item = e.getActionCommand();
         if (item.equals("Exit")){
           System.exit(0);
        }
         if (item.equals("Resizable")){
            if (resizableItem.isSelected())
               setResizable(true);
            else
               setResizable(false);
         }
      }
   }


   public static void main(String[] args){
      JFrame frame = new CheckBoxMenuTest();
      frame.show();
   }
}
