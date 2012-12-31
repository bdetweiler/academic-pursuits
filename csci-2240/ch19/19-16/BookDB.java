import java.sql.*;
import javax.swing.JOptionPane;

public class BookDB{
   private static Connection connection;
   private static Statement scrollStatement;
   private static ResultSet books;

   public static void connect() throws ClassNotFoundException, SQLException{
      Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
      String url = "jdbc:odbc:MurachBooks";
      String user = "Admin";
      String password = "";
      connection = DriverManager.getConnection(url, user, password);
   }

   public static void open() throws SQLException{
      scrollStatement = connection.createStatement(
            ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
      String query = "SELECT BookCode, BookTitle, BookPrice "
                   + "FROM Books ORDER BY BookCode ASC";
      books = scrollStatement.executeQuery(query);
   }
   public static void close(){
      try{
         books.close();
         scrollStatement.close();
      }
      catch(SQLException sqle){
         System.err.println(sqle.getMessage());
      }
   }

   public static Book moveFirst() throws SQLException{
      books.first();
      Book firstBook = new Book(books.getString("BookCode"),
                                books.getString("BookTitle"),
                                books.getDouble("BookPrice"));
      return firstBook;
   }

   public static Book movePrevious() throws SQLException{
      if (books.isFirst() == false)
         books.previous();
     else
         books.first();
     Book previousBook = new Book(books.getString(1),
                                        books.getString(2),
                                        books.getDouble(3));
     return previousBook;

   }
   public static Book moveNext() throws SQLException{
     if (books.isLast() == false)
         books.next();
     else
         books.last();
     Book nextBook = new Book(books.getString(1),
                                  books.getString(2),
                                  books.getDouble(3));
     return nextBook;

   }

   public static Book moveLast() throws SQLException{
      books.last();
      Book lastBook = new Book(books.getString(1),
                                  books.getString(2),
                                  books.getDouble(3));
      return lastBook;
   }
   public static void addRecord(Book book) throws SQLException{
         String query = "INSERT INTO Books (BookCode, BookTitle, BookPrice) " +
            "VALUES ('" + book.getCode() + "', " +
            "'" + book.getTitle() + "', " +
            "'" + book.getPrice() + "')";
         Statement statement = connection.createStatement();
         statement.executeUpdate(query);
         statement.close();
         close();
         open();
      }

   public static void updateRecord(Book book) throws SQLException{
         String query = "UPDATE Books SET " +
                "BookCode = '" + book.getCode() + "', " +
                "BookTitle = '" + book.getTitle() + "', " +
                "BookPrice = '" + book.getPrice() + "' " +
                "WHERE BookCode = '" + book.getCode() + "'";
       Statement statement = connection.createStatement();
       statement.executeUpdate(query);
       statement.close();
   }

   public static void deleteRecord(String bookCode) throws SQLException{
      String query = "DELETE FROM Books " +
         "WHERE BookCode = '" + bookCode + "'";
      Statement statement = connection.createStatement();
      statement.executeUpdate(query);
      statement.close();
      close();
      open();
   }

}
