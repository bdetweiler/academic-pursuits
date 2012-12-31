import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class LabelsGUI extends JFrame{

   public LabelsGUI(){
      setTitle("Adding four labels");
      setBounds(267, 200, 200, 150);
      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      });
      Container contentPane = getContentPane();
      contentPane.add(new MonthlyPaymentPanel());
   }

   public static void main(String[] args){
      JFrame frame = new LabelsGUI();
      frame.show();
   }
}

class MonthlyPaymentPanel extends JPanel implements ActionListener{

   private JLabel amountLabel, rateLabel, yearsLabel, paymentLabel;

   public MonthlyPaymentPanel(){

      JPanel displayPanel = new JPanel();
      displayPanel.setLayout(new FlowLayout(FlowLayout.RIGHT));
      JLabel amountLabel = new JLabel("Loan Amount:");
      JLabel rateLabel = new JLabel("Yearly Interest Rate:");
      JLabel yearsLabel = new JLabel("Number of Years:");
      JLabel paymentLabel = new JLabel("Monthly Payment:");
      displayPanel.add(amountLabel);
      displayPanel.add(rateLabel);
      displayPanel.add(yearsLabel);
      displayPanel.add(paymentLabel);

      setLayout(new BorderLayout());
      add(displayPanel, BorderLayout.CENTER);

   }

   public void actionPerformed(ActionEvent e){
   }
}