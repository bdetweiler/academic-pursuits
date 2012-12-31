import java.sql.*;
import javax.swing.JOptionPane;

public class ConnectDB{
   public static void main(String[] args){

      Connection connection;
      try{
         Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
         String url = "jdbc:odbc:MurachBooks";
         String user = "Admin";
         String password = "";
         connection = DriverManager.getConnection(url, user, password);
         System.out.println("Connection made.");

         Statement statement = connection.createStatement(
         ResultSet.TYPE_SCROLL_SENSITIVE,
         ResultSet.CONCUR_UPDATABLE);
         String query = "SELECT BookCode, BookTitle, BookPrice "
                    + "FROM Books ORDER BY BookCode ASC";
         ResultSet books = statement.executeQuery(query);
         books.first();
         Book firstBook = new Book(books.getString(1),
                                 books.getString(2),
                                 books.getDouble(3));
        System.out.println(firstBook.toString());

        books.next();
        String code2 = books.getString(1);
        String title2 = books.getString(2);
        double price2 = books.getDouble(3);
        Book secondBook = new Book(code2, title2, price2);
        System.out.println(secondBook.toString());

        books.next();
        String code3 = books.getString("BookCode");
        String title3 = books.getString("BookTitle");
        double price3 = books.getDouble("BookPrice");
        Book thirdBook = new Book(code3, title3, price3);
        System.out.println(thirdBook.toString());
      }
      catch (ClassNotFoundException e){
         JOptionPane.showMessageDialog(null, e.getMessage());
         System.exit(1);
      }
      catch (SQLException e){
          JOptionPane.showMessageDialog(null, e.getMessage());
      }

   }

}