public class CountDownEven implements Runnable{
   public void run(){
      Thread currentThread = Thread.currentThread();
      for (int i = 6; i > 0; i-=2){
         System.out.println(currentThread.getName() + " Count " + i);
         Thread.yield();
      }
   }
}
