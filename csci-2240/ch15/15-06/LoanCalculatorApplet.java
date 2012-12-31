import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.text.*;

public class LoanCalculatorApplet extends JApplet{

   public void init(){
      Container contentPane = getContentPane();
      JPanel panel = new LoanCalculatorPanel();
      contentPane.add(panel);
   }

}

class LoanCalculatorPanel extends JPanel implements ActionListener{

   private JTextField amountTextField, rateTextField, yearsTextField,
                  paymentTextField;
   private JLabel amountLabel, rateLabel, yearsLabel, paymentLabel;
   private JButton calculateButton;

   public LoanCalculatorPanel(){

      JPanel displayPanel = new JPanel();
      displayPanel.setLayout(new FlowLayout(FlowLayout.RIGHT));
      amountLabel = new JLabel("Loan Amount:");
      rateLabel = new JLabel("Yearly Interest Rate:");
      yearsLabel = new JLabel("Number of Years:");
      paymentLabel = new JLabel("Monthly Payment:");
      amountTextField = new JTextField(10);
      rateTextField = new JTextField(10);
      yearsTextField = new JTextField(10);
      paymentTextField = new JTextField(10);
      paymentTextField.setEditable(false);
      displayPanel.add(amountLabel);
      displayPanel.add(amountTextField);
      displayPanel.add(rateLabel);
      displayPanel.add(rateTextField);
      displayPanel.add(yearsLabel);
      displayPanel.add(yearsTextField);
      displayPanel.add(paymentLabel);
      displayPanel.add(paymentTextField);

      JPanel buttonPanel = new JPanel();
      buttonPanel.setLayout(new FlowLayout(FlowLayout.RIGHT));
      calculateButton = new JButton("Calculate");
      buttonPanel.add(calculateButton);

      calculateButton.addActionListener(this);

      setLayout(new BorderLayout());
      add(displayPanel, BorderLayout.CENTER);
      add(buttonPanel, BorderLayout.SOUTH);
   }

   public void actionPerformed(ActionEvent e){
      Object source = e.getSource();
      try{
         if (source == calculateButton){
            double amount = Double.parseDouble(amountTextField.getText());
            double rate = Double.parseDouble(rateTextField.getText());
            int years = Integer.parseInt(yearsTextField.getText());
            double monthlyInterest = rate/12/100;
            int months = years * 12;
            double payment = FinancialCalculations.calculateMonthlyPayment(
                           amount, months, monthlyInterest);
            NumberFormat currency = NumberFormat.getCurrencyInstance();
            paymentTextField.setText(currency.format(payment));
         }
      }
      catch (NumberFormatException nfe){
         JOptionPane.showMessageDialog(this, "Invalid data entered.\n"
            + "Please check all numbers and try again.");
      }
   }
}
