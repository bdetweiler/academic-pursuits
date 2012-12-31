//To see practical example of menus, view the LoanCalculatorFrame class in the
//LoanCalculator folder located in Book_Programs/ch13
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class RadioButtonMenuTest extends JFrame implements ActionListener{
   private JRadioButtonMenuItem paymentItem, amountItem;

   public RadioButtonMenuTest(){
      setTitle("Radio Button Menu Item Test");
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
      ButtonGroup group = new ButtonGroup();
      paymentItem = new JRadioButtonMenuItem(
         "Monthly Payment", true);
      amountItem = new JRadioButtonMenuItem(
         "Loan Amount");

      group.add(paymentItem);
      group.add(amountItem);
      calculateMenu.add(paymentItem);
      calculateMenu.add(amountItem);

        exitMenuItem.addActionListener(this);
      paymentItem.addActionListener(this);
      amountItem.addActionListener(this);

      JMenuBar menuBar = new JMenuBar();
      menuBar.add(fileMenu);
      menuBar.add(calculateMenu);

      setJMenuBar(menuBar);

   }

   public void actionPerformed(ActionEvent e){
      Object source = e.getSource();
      if (source instanceof JMenuItem){
         String item = e.getActionCommand();
         if (item.equals("Exit")){
           System.exit(0);
        }
         if (item.equals("Monthly Payment")){
           JOptionPane.showMessageDialog(null, "You selected the Monthly Payment radio button.");
         }
         if (item.equals("Loan Amount")){
            JOptionPane.showMessageDialog(null, "You selected the LoanAmount radio button.");
         }
      }
   }

   public static void main(String[] args){
      JFrame frame = new RadioButtonMenuTest();
      frame.show();
   }
}
