import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.text.*;
import java.util.Date;

public class LoanCalculatorFrame extends JFrame
   implements ActionListener{

   private JTextField amountTextField, rateTextField, yearsTextField,
                        paymentTextField;
   private JLabel amountLabel, rateLabel, yearsLabel, paymentLabel;
   private JButton calculateButton, exitButton;
   private Timer timer;
   private JLabel clockLabel;

   public LoanCalculatorFrame() {
      setTitle("Loan Calculator");
      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      int height = 200;
      int width = 267;
      setBounds((d.width-width)/2, (d.height-height)/2, width, height);
      setResizable(false);
      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      });

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
      exitButton = new JButton("Exit");
      buttonPanel.add(calculateButton);
      buttonPanel.add(exitButton);

      JPanel loanCalculatorPanel = new JPanel();
      loanCalculatorPanel.setLayout(new BorderLayout());
      loanCalculatorPanel.add(displayPanel, BorderLayout.CENTER);
      loanCalculatorPanel.add(buttonPanel, BorderLayout.SOUTH);

      calculateButton.addActionListener(this);
      exitButton.addActionListener(this);

      Container contentPane = getContentPane();
      contentPane.add(loanCalculatorPanel);

      JPanel clockPanel = new JPanel();
      clockPanel.setLayout(new FlowLayout(FlowLayout.RIGHT));
      clockLabel = new JLabel("Starting...");
      clockPanel.add(clockLabel);
      loanCalculatorPanel.add(clockPanel, BorderLayout.NORTH);

      // add code that creates and starts the Timer object here
       timer = new Timer(1000, this);
       timer.setInitialDelay(0);
       timer.start();


   }

   public void actionPerformed(ActionEvent e){
      Object source = e.getSource();
      try{
         if (source == timer){
            Date t = new Date();
            DateFormat df = DateFormat.getTimeInstance(DateFormat.MEDIUM);
            String time = df.format(t);
            clockLabel.setText(time);
         }
         else if (source == exitButton)
            System.exit(0);
         else if (source == calculateButton){
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

   public static void main(String[] args){
      JFrame frame = new LoanCalculatorFrame();
      frame.show();
   }

}
