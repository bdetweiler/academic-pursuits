public class CountDownEven extends Thread{
   public void run(){
      for (int i = 6; i > 0; i-=2){
         System.out.println(this.getName() + " Count " + i);
         Thread.yield();
      }
   }
}