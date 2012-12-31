import java.io.*;
import java.util.*;
import java.util.ArrayList;
import java.lang.*;
import java.text.DecimalFormat;

public class asm
{
	static BufferedReader keyboard = new
		BufferedReader(new InputStreamReader(System.in));

    // public static String binToHex(String binary);

        
	public static void main(String[] args) throws IOException
	{
        String type = "";
        String next = "";
        String answer = "";
       

        while(true)
        {
		    String line = keyboard.readLine();		
            if(line == null)
            {
                break;
            }
            line = line.trim();

            next = line.substring(0, 2);
            line = line.substring(2);
            if(next.equals("db"))
                type = ".byte";
            else if(next.equals("dw"))
                type = ".word";
            else if(next.equals("dd")) 
                type = ".long";
            else if(next.equals("dq"))
                type = ".quad";
            else
                type = ".byte";
            answer = "\t" + type + "\t";
            
            StringTokenizer st = new StringTokenizer(line, ","); 
            // next = st.nextToken();

            try
            {
                while((line = st.nextToken()) != null)
                {
                    char last;
                    line = line.trim(); 
                    // Return last character in token
                    last = line.charAt(line.length() - 1);
                    switch(last)
                    {
                        case 'h':
                            answer += "0x" + 
                                line.substring(0, line.length() - 1) + ", ";
                            break;
                        case 'b':
                            answer += "0x";
                            int total = 0;

                            if(line.substring(0, 1).equals("1"))
                            {
                                total += 8;
                            }
                            if(line.substring(1, 2).equals("1"))
                            {
                                total += 4;
                            }
                            if(line.substring(2, 3).equals("1"))
                            {
                                total += 2;
                            }
                            if(line.substring(3, 4).equals("1"))
                            {
                                total += 1;
                            }

                            answer += Integer.toHexString(total);
                            answer += ", ";
                            break;
                        case 'd':
                            answer += line.substring(0,
                                    line.length() - 1) + ", ";    
                            break;
                        case 'o':
                            answer += "0" + line.substring(0,
                                    line.length() - 1) + ", ";
                            break;
                        default:
                            answer += line + ", ";
                            break;
                    }

                }
            }
            catch(NoSuchElementException nse)
            {
                ;;;
            }

        System.out.println(answer.substring(0, answer.length() - 2) + "\n");
        }

    }
}			
