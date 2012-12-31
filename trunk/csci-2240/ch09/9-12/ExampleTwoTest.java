public class ExampleTwoTest{
   public static void main(String[] args){
      String address = " |805 Main Street|Dallas|TX|12345 ";
      address = address.trim();
      int streetIndex;
      if (address.startsWith("|"))
         streetIndex = 1;
      else
         streetIndex = 0;
      int cityIndex = 1 + address.indexOf("|", streetIndex+1);
      int stateIndex = 1 + address.indexOf("|", cityIndex+1);
      int zipIndex = 1 + address.lastIndexOf("|");

      String street = address.substring(streetIndex, cityIndex-1);
      String city = address.substring(cityIndex, stateIndex-1);
      String state = address.substring(stateIndex, zipIndex-1);
      String zip = address.substring(zipIndex);

      System.out.println(street);
      System.out.println(city);
      System.out.println(state);
      System.out.println(zip);

   }
}
