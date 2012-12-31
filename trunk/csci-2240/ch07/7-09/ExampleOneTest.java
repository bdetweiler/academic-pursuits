import java.util.*;
import java.text.DateFormat;

public class ExampleOneTest{
   public static void main(String[] args){
      Date now = new Date();
      DateFormat defaultDate = DateFormat.getDateTimeInstance();
      String nowString = defaultDate.format(now);
      System.out.println(nowString);
   }
}
