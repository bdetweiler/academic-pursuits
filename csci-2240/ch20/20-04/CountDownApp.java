public class CountDownApp{
   public static void main(String[] args){
      Thread count1 = new CountDownEven();
      Thread count2 = new CountDownOdd();
      count1.start();
      count2.start();
   }
}