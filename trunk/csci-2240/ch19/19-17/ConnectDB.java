import java.sql.*;
import javax.swing.JOptionPane;
import java.util.Vector;

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
         Vector columnNames = getColumnNames(books);
         for (int i = 0; i< columnNames.size(); i++){
          System.out.println(columnNames.elementAt(i));
       }

       Vector rowNames = getRows(books);
       for (int i = 0; i< rowNames.size(); i++){
            System.out.println(rowNames.elementAt(i));
       }

      }
      catch (ClassNotFoundException e){
         JOptionPane.showMessageDialog(null, e.getMessage());
         System.exit(1);
      }
      catch (SQLException e){
          JOptionPane.showMessageDialog(null, e.getMessage());
      }

   }
   public static Vector getColumnNames(ResultSet results) throws SQLException{
      Vector columnNames = new Vector();
      ResultSetMetaData metaData = results.getMetaData();
      int columnCount = metaData.getColumnCount();
      for (int i = 1; i <= columnCount; i++)
         columnNames.add(metaData.getColumnName(i));
      return columnNames;
   }
   public static Vector getRows(ResultSet results) throws SQLException{
      Vector rows = new Vector();
      ResultSetMetaData metaData = results.getMetaData();
      int columnCount = metaData.getColumnCount();
      while (results.next()){
         Vector row = new Vector();
         for (int i = 1; i <= columnCount; i++){
            if (metaData.getColumnType(i) == Types.VARCHAR)
               row.add(results.getString(i));
            else if (metaData.getColumnType(i) == Types.INTEGER)
               row.add(new Integer(results.getInt(i)));
            else if (metaData.getColumnType(i) == 2)
               row.add(new Double(results.getDouble(i)));
         }
         rows.add(row);
      }
      return rows;
   }



}