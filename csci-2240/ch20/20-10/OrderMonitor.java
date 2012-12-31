public class OrderMonitor{
   private boolean request = false;
   private String orderString;

   public synchronized String retrieveOrder(){
      while (request == false){
         try{
            wait();
         }
         catch(InterruptedException e){}
      }
      request = false;
      notifyAll();
      return orderString;
   }

   public synchronized void sendOrder(String s){
      while(request == true){
         try{
            wait();
         }
         catch(InterruptedException e){}
      }
      request = true;
      notifyAll();
      orderString = s;
   }

}