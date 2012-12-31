import javax.swing.*;
import java.util.*;
import java.text.*;

public class Alarm{
   private java.util.Timer timer;

   public Alarm(){
      GregorianCalendar alarmGregDateTime =
         new GregorianCalendar(2001, Calendar.JUNE, 23, 14, 24);
      Date alarmDateTime = alarmGregDateTime.getTime();
      timer = new java.util.Timer();
      timer.schedule(new AlarmTask(), alarmDateTime);
   }

   public static void main(String[] args){
      Alarm alarm = new Alarm();
   }
}

class AlarmTask extends TimerTask{
   public void run(){
      JOptionPane.showMessageDialog(null, "Time for your meeting!");
      System.exit(0);
   }
}
