import java.util.Arrays;

public class ExampleOneTest{
   public static void main(String[] args){
      int[] quantities = new int[5];
      Arrays.fill(quantities, 1);
      for (int i = 0; i<quantities.length; i++){
         System.out.println(quantities[i]);
      }

      Arrays.fill(quantities, 0, 2, 4);
      for (int i = 0; i<quantities.length; i++){
         System.out.println(quantities[i]);
      }

      Book[] books = new Book[5];
      Arrays.fill(books, new Book("warp"));
      for (int i = 0; i<books.length; i++){
         System.out.println(books[i].getTitle());
      }

      String[] bookCodes = {"warp", "mbdk"};
      String[] newBookCodes = {"warp", "citr"};
      boolean bookCodesEqual = Arrays.equals(bookCodes, newBookCodes);
      System.out.println("\nBook codes equal: " + bookCodesEqual);

         int[] numbers = {2,6,4,1,8,5,9,3,7,0};
         Arrays.sort(numbers);
         for (int i = 0; i<numbers.length; i++){
         System.out.println(numbers[i]);
      }

      double[][] grades = {{92.3, 88.0, 95.2, 90.5},
                         {70.2, 79.1, 82.0, 69.8},
                          {88.5, 92.0, 84.4, 97.9}};
      for (int i = 0; i < grades.length; i++){
            Arrays.sort(grades[i]);
      }
      for (int i = 0; i<grades.length; i++){
         String row = "";
         for (int j = 0; j<grades[i].length; j++){
            row += grades[i][j] + " ";
         }
         System.out.println(row);
      }
   }
}
