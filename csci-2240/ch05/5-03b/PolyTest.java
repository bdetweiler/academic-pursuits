import javax.swing.JOptionPane;
public class PolyTest{
   public static void main(String[] args){
      boolean keyCodeExists = false;
      String keyCode = JOptionPane.showInputDialog("Keycode exists, Y or N");
      if (keyCode.equals("Y")) keyCodeExists = true;
      BookOrder bookOrder = null;
      if (keyCodeExists)
            bookOrder = new DiscountBookOrder("WARP", 2, "a10");
      else
            bookOrder = new BookOrder("WARP", 2);
      bookOrder.setTotal();  //calls the setTotal method in the appropriate class.
      System.out.println(bookOrder.getTotal());
   }
}
