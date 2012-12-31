public class Book{
   private String code;
   private String title;
   private double price;

   public Book(){
      this("", "", 11.95);
   }

   public Book(String bookCode, String bookTitle, double bookPrice){
      code = bookCode;
      title = bookTitle;
      price = bookPrice;
   }

   public String getCode(){return code;}
   public String getTitle(){return title;}
   public double getPrice(){return price;}

   public void setCode(String bookCode){code = bookCode;}
   public void setTitle(String bookTitle){title = bookTitle;}
   public void setPrice(double bookPrice){price = bookPrice;}

   public String toString(){
     return "Code: " + code + "\n" +
             "Title: " + title + "\n" +
             "Price: " + price + "\n";
   }

}