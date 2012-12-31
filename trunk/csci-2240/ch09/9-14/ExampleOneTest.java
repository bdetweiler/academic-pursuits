public class ExampleOneTest{
   public static void main(String[] args){
      StringBuffer phoneNumber = new StringBuffer();
      phoneNumber.append("977");
      phoneNumber.append("555");
      phoneNumber.append("1212");
      phoneNumber.insert(3, '-');
      phoneNumber.insert(7, '-');
      System.out.println(phoneNumber);

      String areaCode = phoneNumber.substring(0,3);
      String prefix = phoneNumber.substring(4,7);
      String suffix = phoneNumber.substring(8);
      System.out.println(areaCode);
      System.out.println(prefix);
      System.out.println(suffix);

      for(int i = 0; i < phoneNumber.length(); i++){
         if (phoneNumber.charAt(i) == '-')
            phoneNumber.deleteCharAt(i);
      }
      System.out.println(phoneNumber);
   }
}


