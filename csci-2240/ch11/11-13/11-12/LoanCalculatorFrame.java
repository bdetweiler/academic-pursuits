import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class LoanCalculatorFrame extends JFrame{
   public LoanCalculatorFrame(){
      setTitle("Loan Calculator");
      setBounds(267, 200, 267, 200);
      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      });
      Container contentPane = getContentPane();
      contentPane.add(new LoanCalculatorPanel());
   }
}
class LoanCalculatorPanel extends JPanel implements ActionListener{

   private JButton calculateButton, exitButton;

   public LoanCalculatorPanel(){
      JPanel buttonPanel = new JPanel();
      buttonPanel.setLayout(new FlowLayout(FlowLayout.RIGHT));
      calculateButton = new JButton("Calculate");
      calculateButton.addActionListener(this);
      exitButton = new JButton("Exit");
      exitButton.addActionListener(this);
      buttonPanel.add(calculateButton);
      buttonPanel.add(exitButton);

      setLayout(new BorderLayout());
      add(buttonPanel, BorderLayout.SOUTH);
   }

   public void actionPerformed(ActionEvent e){
      Object source = e.getSource();
      if (source == exitButton) System.exit(0);
      else if (source == calculateButton)
         JOptionPane.showMessageDialog(null,
            "You pressed the Calculate button.");
   }
}
