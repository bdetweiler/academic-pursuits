import java.io.*;
import java.util.*;

public class BookIO{
   private static Book book = null;
   private static String[] codes = null;
   private static RandomAccessFile randomFile = null;

   private static final File BOOK_FILE = new File("books.dat");
   private static final int CODE_SIZE = 4;
   private static final int TITLE_SIZE = 20;
   private static final int RECORD_SIZE = CODE_SIZE*2 + TITLE_SIZE*2 + 8;


   public static void open() throws IOException{
      randomFile = new RandomAccessFile(BOOK_FILE, "rw");
      codes = readCodes();
   }
   public static void close(){
      try{
         randomFile.close();
      }
      catch(IOException e){
         System.out.println("I/OException thrown when closing file.");
      }
   }
   public static int getRecordCount() throws IOException{
      long length = BOOK_FILE.length();
      int recordCount = (int) (length / RECORD_SIZE);
      return recordCount;
   }
   public static String readString(DataInput in, int length)
   throws IOException{
      String s = "";
      int i = 0;
      while (i < length){
         char c = in.readChar();
         if (c!=0)
            s += c;
         i++;
      }
      return s;
   }
   public static Book readRecord(int recordNumber) throws IOException{
      randomFile.seek((recordNumber-1) * RECORD_SIZE);
      String code = readString(randomFile, CODE_SIZE);
      String title = readString(randomFile, TITLE_SIZE);
      double price = randomFile.readDouble();
      book = new Book(code, title, price);
      return book;
   }
   public static Book readRecord(String bookCode) throws IOException{
      int recordNumber = getRecordNumber(bookCode);
      book = readRecord(recordNumber);
      return book;
   }
   public static int getRecordNumber(String bookCode) throws IOException{
      int match = -1;
      int i = 0;
      boolean flag = true;
      while ((i < getRecordCount()) && (flag==true)){
         if (bookCode.equals(codes[i])){
            match = i+1;
            flag = false;
         }
         i++;
      }
      return match;
   }

   public static String[] readCodes() throws IOException{
      codes = new String[getRecordCount()];
      for (int i = 0; i < getRecordCount(); i++){
         randomFile.seek(i * RECORD_SIZE);
         codes[i] = readString(randomFile, CODE_SIZE);
      }
      return codes;
   }
   public static String[] readTitles() throws IOException{
      String[] titles = new String[getRecordCount()];
      for (int i = 0; i < getRecordCount(); i++){
         randomFile.seek(i * RECORD_SIZE + 8);
         titles[i] = readString(randomFile, TITLE_SIZE);
      }
      return titles;
   }

public static void writeString(DataOutput out, String s, int length)
   throws IOException{
      for (int i = 0; i < length; i++){
         if (i < s.length())
            out.writeChar(s.charAt(i));
         else
            out.writeChar(0);
      }
   }

public static void writeRecord(Book book, int recordNumber)
   throws IOException{
      randomFile.seek((recordNumber-1) * RECORD_SIZE);
      writeString(randomFile, book.getCode(), CODE_SIZE);
      writeString(randomFile, book.getTitle(), TITLE_SIZE);
      randomFile.writeDouble(book.getPrice());
   }
public static Book moveFirst() throws IOException{
      book = readRecord(1);
      return book;
   }

   public static Book movePrevious() throws IOException{
      int recordNumber = getRecordNumber(book.getCode());
      if (recordNumber != 1)
         book = readRecord(recordNumber - 1);
      return book;
   }

   public static Book moveNext() throws IOException{
      int recordNumber = getRecordNumber(book.getCode());
      if (recordNumber != getRecordCount())
         book = readRecord(recordNumber + 1);
      return book;
   }

   public static Book moveLast() throws IOException{
      int lastRecordNumber = getRecordCount();
      book = readRecord(lastRecordNumber);
      return book;
   }
   public static void addRecord(Book addBook) throws IOException{
      writeRecord(addBook, getRecordCount() + 1);
      close();
      open();
   }

   public static void updateRecord(Book book) throws IOException{
      int recordNumber = getRecordNumber(book.getCode());
      writeRecord(book, recordNumber);
   }
   public static void deleteRecord(String bookCode) throws IOException{
      int recordNumber = getRecordNumber(bookCode);
      Vector books = new Vector();
      for (int i = 0; i< getRecordCount(); i++){
         books.add(readRecord(i+1));
      }
      books.remove(recordNumber-1);
      randomFile.setLength(RECORD_SIZE *(getRecordCount() -1));
      for (int i = 0; i<books.size(); i++){
         writeRecord((Book)books.elementAt(i),i+1);
      }
      if (recordNumber < getRecordCount())
         book = readRecord(recordNumber);
      else
         book = readRecord(getRecordCount()-1);
      close();
      open();
   }
}
