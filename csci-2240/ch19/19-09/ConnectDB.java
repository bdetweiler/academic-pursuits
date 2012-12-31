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
         JOptionPane.showMessageDialog(null, "Connection made.");
      }
      catch (ClassNotFoundException e){
         JOptionPane.showMessageDialog(null, "ClassNotFound " + e.getMessage());
         System.exit(1);
      }
      catch (SQLException e){
          JOptionPane.showMessageDialog(null, e.getMessage());
      }
   }

}