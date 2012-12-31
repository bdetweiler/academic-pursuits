import java.util.Vector;

public class ExampleOneTest{
   public static void main(String[] args){
      Vector codesVector = new Vector();
      codesVector.add("mbdk");
      codesVector.add("citr");
      codesVector.add(0, "warp");

      for (int i = 0; i < codesVector.size(); i++){
         String code = (String) codesVector.get(i);
         System.out.println(code);
      }

      String[] codesArray = new String[codesVector.size()];
      codesVector.copyInto(codesArray);
      for (int i = 0; i<codesArray.length; i++){
         System.out.println(codesArray[i]);
      }

   }
}