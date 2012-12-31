import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import java.text.*;
import java.sql.*;

public class BookFrame extends JFrame{
   public BookFrame(){
      setTitle("Book Maintenance");
      Toolkit tk = Toolkit.getDefaultToolkit();
      Dimension d = tk.getScreenSize();
      int width = 400, height = 200;
      setBounds((d.width - width)/2, (d.height - height)/2, width, height);
      setResizable(false);
      addWindowListener(new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            BookDB.close();
            System.exit(0);
       }
      });
      Container contentPane = getContentPane();
      BookPanel panel = new BookPanel();
      contentPane.add(panel);
   }
   public static void main(String[] args){
      JFrame frame = new BookFrame();
      frame.show();
   }
}

class BookPanel extends JPanel implements ActionListener,
   DocumentListener, KeyListener{

   private JButton addButton, updateButton, deleteButton, exitButton,
                   firstButton, prevButton, nextButton, lastButton;
   private JLabel codeLabel, titleLabel, priceLabel;
   private JTextField codeField, titleField, priceField;
   public static boolean addFlag = false;
   public static NumberFormat currency = NumberFormat.getCurrencyInstance();
   Book currentBook = null;

   public BookPanel(){

      codeLabel = new JLabel("Code: ");
      codeField = new JTextField("", 7);
      titleLabel = new JLabel("Title: ");
      titleField = new JTextField("", 26);
      priceLabel = new JLabel("Price: ");
      priceField = new JTextField("", 7);

      JPanel updatePanel = new JPanel();
      addButton = new JButton("Add");
      updateButton = new JButton("Update");
      deleteButton = new JButton("Delete");
      exitButton = new JButton("Exit");
      updatePanel.add(addButton);
      updatePanel.add(updateButton);
      updatePanel.add(deleteButton);
      updatePanel.add(exitButton);

      JPanel navigationPanel = new JPanel();
      firstButton = new JButton("First");
      prevButton = new JButton("Prev");
      nextButton = new JButton("Next");
      lastButton = new JButton("Last");
      navigationPanel.add(firstButton);
      navigationPanel.add(prevButton);
      navigationPanel.add(nextButton);
      navigationPanel.add(lastButton);

      addButton.addActionListener(this);
      updateButton.addActionListener(this);
      deleteButton.addActionListener(this);
      exitButton.addActionListener(this);
      firstButton.addActionListener(this);
      prevButton.addActionListener(this);
      nextButton.addActionListener(this);
      lastButton.addActionListener(this);
      codeField.addKeyListener(this);
      titleField.addKeyListener(this);
      priceField.addKeyListener(this);
      codeField.getDocument().addDocumentListener(this);
      titleField.getDocument().addDocumentListener(this);
      priceField.getDocument().addDocumentListener(this);

      setLayout(new GridBagLayout());
      GridBagConstraints c = new GridBagConstraints();
      c.weightx = 100;
      c.weighty = 100;
      c.ipadx = 5;

      c.anchor = GridBagConstraints.EAST;
      c = getConstraints(c, 1, 1, 1, 1);
      add(codeLabel, c);
      c = getConstraints(c, 1, 2, 1, 1);
      add(titleLabel, c);
      c = getConstraints(c, 1, 3, 1, 1);
      add(priceLabel, c);

      c.anchor = GridBagConstraints.WEST;
      c = getConstraints(c, 2, 1, 3, 1);
      add(codeField, c);
      c = getConstraints(c, 2, 2, 3, 1);
      add(titleField, c);
      c = getConstraints(c, 2, 3, 3, 1);
      add(priceField, c);

      c.anchor = GridBagConstraints.CENTER;
      c = getConstraints(c, 1, 4, 4, 1);
      add(updatePanel, c);
      c = getConstraints(c, 1, 5, 4, 1);
      add(navigationPanel, c);

      try{
         BookDB.connect();
         BookDB.open();
         currentBook = BookDB.moveFirst();

      }
      catch (ClassNotFoundException e){
         JOptionPane.showMessageDialog(null, e.getMessage());
         System.exit(1);
      }
      catch (SQLException e){
         JOptionPane.showMessageDialog(null, e.getMessage());
      }
      performBookDisplay();
      enableButtons(true);
   }

   private GridBagConstraints getConstraints(GridBagConstraints c,
      int x, int y, int width, int height){
      c.gridx = x;
      c.gridy = y;
      c.gridwidth = width;
      c.gridheight = height;
      return c;
   }

   private void performBookDisplay(){
      codeField.setText(currentBook.getCode());
      titleField.setText(currentBook.getTitle());
      priceField.setText(currency.format(currentBook.getPrice()));
   }

   private void enableButtons(boolean flag1){
      boolean flag2 = false;
      if (flag1 == false)
         flag2 = true;
      updateButton.setEnabled(flag2);
      addButton.setEnabled(flag1);
      deleteButton.setEnabled(flag1);
      firstButton.setEnabled(flag1);
      nextButton.setEnabled(flag1);
      prevButton.setEnabled(flag1);
      lastButton.setEnabled(flag1);
   }

   private double parseCurrency(String currencyString){
      if (currencyString.charAt(0) == '$')
          currencyString = currencyString.substring(1);
      return Double.parseDouble(currencyString);
   }

   public void actionPerformed(ActionEvent e){
      try{
         Object source = e.getSource();
         if (source == exitButton){
          BookDB.close();
          System.exit(0);
       }
         else if (source == firstButton){
            currentBook = BookDB.moveFirst();
            performBookDisplay();
            enableButtons(true);
         }
         else if (source == prevButton){
            currentBook = BookDB.movePrevious();
            performBookDisplay();
            enableButtons(true);
         }
         else if (source == nextButton){
            currentBook = BookDB.moveNext();
            performBookDisplay();
            enableButtons(true);
         }
         else if (source == lastButton){
            currentBook = BookDB.moveLast();
            performBookDisplay();
            enableButtons(true);
         }
         else if (source == addButton){
            codeField.requestFocus();
            enableButtons(false);
            codeField.setText("");
            titleField.setText("");
            priceField.setText("");
            addFlag = true;
         }
         else if (source == updateButton){
            double price = parseCurrency(priceField.getText());
            Book book = new Book(codeField.getText(),
                                 titleField.getText(),
                                 price);
            if (addFlag == false){
            BookDB.updateRecord(book);
            currentBook = book;
         }
         if (addFlag == true){
            BookDB.addRecord(book);
            currentBook = BookDB.moveFirst();
            addFlag = false;
         }
            currentBook = book;
            performBookDisplay();
            enableButtons(true);
         }
         else if(source == deleteButton){
            BookDB.deleteRecord(currentBook.getCode());
            firstButton.requestFocus();
            firstButton.doClick();
            performBookDisplay();
            enableButtons(true);
         }
      }
      catch (NumberFormatException nfe){
         JOptionPane.showMessageDialog(this, nfe.getMessage());
      }
      catch (SQLException sqle){
         JOptionPane.showMessageDialog(this, sqle.getMessage());
      }
   }

   public void keyPressed(KeyEvent e){
      int keyCode = e.getKeyCode();
      if (keyCode == KeyEvent.VK_ESCAPE){
      performBookDisplay();
      enableButtons(true);
      codeField.requestFocus();
      }
   }
   public void keyReleased(KeyEvent e){
   }
   public void keyTyped(KeyEvent e){
   }

   public void insertUpdate(DocumentEvent e){
      enableButtons(false);
   }
   public void removeUpdate(DocumentEvent e){
      enableButtons(false);
   }
   public void changedUpdate(DocumentEvent e){
   }

}
