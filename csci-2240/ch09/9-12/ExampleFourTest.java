public class ExampleFourTest{
   public static void main(String[] args){
      String phoneNumber1 = "977-555-1212";
      String phoneNumber2 = "";
      for(int i = 0; i < phoneNumber1.length(); i++){
         if (phoneNumber1.charAt(i) != '-')
            phoneNumber2 += phoneNumber1.charAt(i);
      }
      System.out.println(phoneNumber2);
   }
}
