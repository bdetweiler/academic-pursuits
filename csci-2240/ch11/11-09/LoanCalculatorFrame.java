import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class LoanCalculatorFrame extends JFrame implements ActionListener{

   private JButton calculateButton, exitButton;

   public LoanCalculatorFrame(){
      setTitle("Loan Calculator");

      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      int width = 267;
      int height = 200;
      setBounds((d.width - width)/2, (d.height - height)/2, width, height);

      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      });

      JPanel panel = new JPanel();
      calculateButton = new JButton("Calculate");
      calculateButton.addActionListener(this);
      exitButton = new JButton("Exit");
      exitButton.addActionListener(this);
      panel.add(calculateButton);
      panel.add(exitButton);
      Container contentPane = getContentPane();
      contentPane.add(panel);
   }

   public void actionPerformed(ActionEvent e){
      Object source = e.getSource();
      if (source == exitButton)
         System.exit(0);
      else if (source == calculateButton){
         JOptionPane.showMessageDialog(null,
                  "You pressed the Calculate button.");
      }
   }
}
