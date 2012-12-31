import javax.swing.*;

public class BookOrderFrame extends JFrame{
   public BookOrderFrame(){
      setTitle("Book Order");
      setBounds(267, 200, 267, 200);
   }

   public static void main(String[] args){
      JFrame frame = new BookOrderFrame();
      frame.show();
   }
}
