import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import java.text.*;

public class LoanCalculatorApplet extends Applet{

   public void init(){
      Panel panel = new LoanCalculatorPanel();
      setLayout(new BorderLayout());
      add(panel, BorderLayout.CENTER);
   }

}

class LoanCalculatorPanel extends Panel implements ActionListener{

   private TextField amountTextField, rateTextField, yearsTextField,
                      paymentTextField;
   private Label amountLabel, rateLabel, yearsLabel, paymentLabel;
   private Button calculateButton;

   public LoanCalculatorPanel(){

      Panel displayPanel = new Panel();
      displayPanel.setLayout(new FlowLayout(FlowLayout.RIGHT));
      amountLabel = new Label("Loan Amount:");
      rateLabel = new Label("Yearly Interest Rate:");
      yearsLabel = new Label("Number of Years:");
      paymentLabel = new Label("Monthly Payment:");
      amountTextField = new TextField(10);
      rateTextField = new TextField(10);
      yearsTextField = new TextField(10);
      paymentTextField = new TextField(10);
      paymentTextField.setEditable(false);
      displayPanel.add(amountLabel);
      displayPanel.add(amountTextField);
      displayPanel.add(rateLabel);
      displayPanel.add(rateTextField);
      displayPanel.add(yearsLabel);
      displayPanel.add(yearsTextField);
      displayPanel.add(paymentLabel);
      displayPanel.add(paymentTextField);

      Panel buttonPanel = new Panel();
      buttonPanel.setLayout(new FlowLayout(FlowLayout.RIGHT));
      calculateButton = new Button("Calculate");
      calculateButton.addActionListener(this);
      buttonPanel.add(calculateButton);

      setLayout(new BorderLayout());
      add(displayPanel, BorderLayout.CENTER);
      add(buttonPanel, BorderLayout.SOUTH);
   }

   public void actionPerformed(ActionEvent e){
      Object source = e.getSource();
      try{
         if (source == calculateButton){
            //double amount = Double.parseDouble(amountTextField.getText());
            //double rate = Double.parseDouble(rateTextField.getText());
            double amount = new Double(amountTextField.getText()).doubleValue();
            double rate = new Double(rateTextField.getText()).doubleValue();
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
      }
   }
}
