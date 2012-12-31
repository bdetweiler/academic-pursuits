public class ExampleThreeTest{
   public static void main(String[] args){
      String phoneNumber1 = "9775551212";
      String phoneNumber2 = phoneNumber1.substring(0, 3);
      phoneNumber2 += "-";
      phoneNumber2 += phoneNumber1.substring(3, 6);
      phoneNumber2 += "-";
      phoneNumber2 += phoneNumber1.substring(6);
      System.out.println(phoneNumber2);
   }
}
