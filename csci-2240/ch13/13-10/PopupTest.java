//To see practical example of popup menus, view the LoanCalculatorFrame class in the
//LoanCalculator folder located in Book_Programs/ch13

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class PopupTest extends JFrame implements ActionListener{
   private JPopupMenu popupMenu;
   private JCheckBoxMenuItem resizablePopupItem;
   private JMenuItem exitPopupItem;

   public PopupTest(){
      setTitle("Popup Menu Test");
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

      popupMenu = new JPopupMenu();
      resizablePopupItem = new JCheckBoxMenuItem("Resizable", false);
      exitPopupItem = new JMenuItem("Exit");
      popupMenu.add(resizablePopupItem);
      popupMenu.addSeparator();
      popupMenu.add(exitPopupItem);

      resizablePopupItem.addActionListener(this);
      exitPopupItem.addActionListener(this);
        exitMenuItem.addActionListener(this);

      JMenuBar menuBar = new JMenuBar();
      menuBar.add(fileMenu);
      menuBar.add(calculateMenu);

      setJMenuBar(menuBar);

      Container contentPane = getContentPane();
      contentPane.addMouseListener(new MouseAdapter(){
         public void mouseReleased(MouseEvent e){
            if (e.isPopupTrigger())
               popupMenu.show(e.getComponent(), e.getX(), e.getY());
         }
      });
   }

   public void actionPerformed(ActionEvent e){
      Object source = e.getSource();
      if (source instanceof JMenuItem){
         String item = e.getActionCommand();
         if (item.equals("Exit")){
           System.exit(0);
        }
         if (item.equals("Resizable")){
            if (resizablePopupItem.isSelected())
               setResizable(true);
            else
               setResizable(false);
         }
      }
   }


   public static void main(String[] args){
      JFrame frame = new PopupTest();
      frame.show();
   }
}
