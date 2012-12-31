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

         String preparedSQL = "SELECT BookCode, BookTitle, BookPrice " +
                            "FROM Books WHERE BookCode = ?";
         PreparedStatement ps = connection.prepareStatement(preparedSQL,
            ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
         ps.setString(1, "CC2R");
         ResultSet books = ps.executeQuery();

         books.first();
         Book firstBook = new Book(books.getString(1),
                                 books.getString(2),
                                 books.getDouble(3));
         System.out.println(firstBook.toString());

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