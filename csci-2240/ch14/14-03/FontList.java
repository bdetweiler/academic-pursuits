import java.awt.*;

public class FontList{
   public static void main(String[] args){
      GraphicsEnvironment ge = null;
      ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
      String[] fonts = ge.getAvailableFontFamilyNames();
      for (int i = 0; i<fonts.length; i++){
         System.out.println(fonts[i]);
      }
   }
}

