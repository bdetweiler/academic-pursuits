public class CountDownOdd implements Runnable{
   public void run(){
      Thread currentThread = Thread.currentThread();
      for (int i = 5; i > 0; i -= 2){
         System.out.println(currentThread.getName() + " Count " + i);
         Thread.yield();
      }
   }
}
