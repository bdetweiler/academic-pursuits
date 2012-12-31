import javax.swing.*;
import java.awt.event.*;

public class LoanCalculatorFrame extends JFrame{
   public LoanCalculatorFrame(){
        setTitle("Loan Calculator");
        setBounds(267, 200, 267, 200);
        addWindowListener(new WindowAdapter(){
           public void windowClosing(WindowEvent e){
              System.exit(0);
           }
        });
   }

}

