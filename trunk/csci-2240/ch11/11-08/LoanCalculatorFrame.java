import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class LoanCalculatorFrame extends JFrame{
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
       JButton calculateButton = new JButton("Calculate");
       JButton exitButton = new JButton("Exit");
       panel.add(calculateButton);
       panel.add(exitButton);

       Container contentPane = getContentPane();
       contentPane.add(panel);
   }

}

