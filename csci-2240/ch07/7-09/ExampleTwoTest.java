import java.util.*;
import java.text.DateFormat;

public class ExampleTwoTest{
   public static void main(String[] args){
      GregorianCalendar gregEndDate = new GregorianCalendar(2005,11,31,7,30);
      Date endDate = gregEndDate.getTime();
      DateFormat defaultDate = DateFormat.getDateInstance();
      String endDateString = defaultDate.format(endDate);
      System.out.println(endDateString);
   }
}
