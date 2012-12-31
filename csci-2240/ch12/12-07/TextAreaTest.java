import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
import javax.swing.event.*;

public class TextAreaTest extends JFrame implements DocumentListener{
   private JTextArea commentTextArea;
   private JButton monitorButton;

   public TextAreaTest(){
      setTitle("Text Area Test");
      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      int height = d.height;
      int width = d.width;
      setBounds(width/4, height/4, 350, 200);
      setResizable(false);

      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
     });
      Container contentPane = getContentPane();
      JPanel displayPanel = new JPanel();

      commentTextArea = new JTextArea(2, 10);
      commentTextArea.setLineWrap(true);
      commentTextArea.setWrapStyleWord(true);
      commentTextArea.getDocument().addDocumentListener(this);
      JScrollPane commentScroll = new JScrollPane(commentTextArea);
      displayPanel.add(commentScroll);

      monitorButton = new JButton("Text Area is not being modified.");
      displayPanel.add(monitorButton);
      contentPane.add(displayPanel);
   }

   public void insertUpdate(DocumentEvent e){
      if (e.getDocument() == commentTextArea.getDocument())
         monitorButton.setText("Text Area is modified.");
   }
   public void removeUpdate(DocumentEvent e){}
   public void changedUpdate(DocumentEvent e){}

   public static void main(String[] args){
      JFrame frame = new TextAreaTest();
      frame.show();
   }
}

