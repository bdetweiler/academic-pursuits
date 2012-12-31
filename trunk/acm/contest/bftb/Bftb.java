import java.io.*;
import java.util.*;
import java.util.ArrayList;
import java.lang.*;
import java.text.DecimalFormat;

public class Bftb
{
	static BufferedReader keyboard = new
		BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws IOException
	{

	  	int numCases = 0;
		int numComponents = 0;
		String component = "";
		double speedup = 0;
		double cost = 0;
		double speedupOverall = 0;
		double factor = 0;
		String winner = "";
		double max = 0;
		double bftb = 0;
		DecimalFormat fourDec = new DecimalFormat("0.0000");
		DecimalFormat oneDec  = new DecimalFormat("0.0");
		ArrayList list = new ArrayList();
		
		String whatever = keyboard.readLine();		
		numCases = Integer.parseInt(whatever);
		
		for(int i = 0; i < numCases; ++i)
		{
			numComponents = Integer.parseInt(keyboard.readLine());

			for(int j = 0; j < numComponents; ++j)
			{				
			  	StringTokenizer st = new StringTokenizer(keyboard.readLine(), ":");
				component = st.nextToken();
				speedup   = Double.parseDouble(st.nextToken());
				cost		 = Double.parseDouble(st.nextToken());
				
				if(cost < 200)
				{

					if(component.substring(0, 1).equals("M"))
					{
						factor = 0.2;
					}
					else if(component.substring(0, 1).equals("G"))
					{
						factor = 0.35;
					}
					else if(component.substring(0, 1).equals("D"))
					{
					 	factor = 0.2;
					}
					else if(component.substring(0, 1).equals("C"))
					{
						factor = 0.25;
					}
							
					speedupOverall = (1/((1 - factor) + (factor/speedup))) - 1;
					bftb = (speedupOverall / cost) * 100;
								
					
							
					if(bftb > max)
					{
						max    = bftb;
						winner = component;
					} 
					
				}
				else // cost > 200
				{
					bftb = -1.0;
				}
				if(bftb == -1)
				{
					list.add(j, component + ":" + oneDec.format(bftb));
				}
				else
				{
					list.add(j, component + ":" + fourDec.format(bftb));
				}
				if(j == numComponents - 1)
				{
					System.out.println();
					for(int g = 0; g < j; ++g)
					{
						 StringTokenizer st1 = new StringTokenizer((String)list.get(g), ":");
						 StringTokenizer st2 = new StringTokenizer((String)list.get(j), ":");
					 	 st1.nextToken();
						 double num = Double.parseDouble(st1.nextToken());
					 	 st2.nextToken();
						 double num2 = Double.parseDouble(st2.nextToken());
				       if(num < num2)
					 	 {
						  	String tmp = (String)list.get(g);
							list.set(g, list.get(j));
							list.set(j, tmp);
						 }
					}			
					for(int h = 0; h < list.size(); ++h)
					{
						System.out.println(list.get(h));
					}
				}	
			} // End for j
			
			if(max != -1.0)
			{
				System.out.println("You should buy " + winner + 
					" with the BFTB index of " + fourDec.format(max) + ".");	
			}
			else
			{
				System.out.println("You can not afford any components.");
			}
		} // End for i
	}
}			