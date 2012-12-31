public class OrderMonitorTest{
   public static void main(String[] args){
      OrderMonitor monitor = new OrderMonitor();

      Seller s = new Seller(monitor);
      //s.setDaemon(true);
      s.start();

      Buyer b1 = new Buyer(monitor, "Order one");
      b1.start();

      Buyer b2 = new Buyer(monitor, "Order two");
      b2.start();

      //Buyer b3 = new Buyer(monitor, "Order three");
      //b3.start();

   }
}