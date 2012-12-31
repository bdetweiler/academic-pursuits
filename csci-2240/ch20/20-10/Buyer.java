public class Buyer extends Thread{
   private OrderMonitor monitor;
   private String orderString;

   public Buyer(OrderMonitor m, String s){
      monitor = m;
      orderString = s;
   }

   public void run(){
      monitor.sendOrder(orderString);
      System.out.println("Buyer sent: " + orderString);
   }

}