public class Seller extends Thread{
   private OrderMonitor monitor;

   public Seller(OrderMonitor m){
      monitor = m;
   }

   public void run(){
      while (true){
         String orderString = monitor.retrieveOrder();
         System.out.println("Seller retrieved: " + orderString);
         //code that processes the order
      }
   }
}
