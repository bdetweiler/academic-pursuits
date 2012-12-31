public class ExampleTwoTest{
   public static void main(String[] args){
      StringBuffer name = new StringBuffer(8);
      int capacity1 = name.capacity();    //capacity1 is 8
      System.out.println("StringBuffer: " + name + " Initial Capacity: " + capacity1);
      name.append("Raymond R. Thomas");
      int length = name.length();         //length is 17
      int capacity2 = name.capacity();    //capacity2 is 18 (2 * capacity1 + 2)
      System.out.println("StringBuffer: " + name + " Final Capacity: " + capacity2);
   }
}


