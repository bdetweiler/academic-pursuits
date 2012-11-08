package net.projecteuler.problem89;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.InputStreamReader;

import org.apache.commons.lang.time.StopWatch;
import org.junit.Test;


public class Problem89 {

    @Test
    public void testProblem55() {
        
        StopWatch sw = new StopWatch();
        sw.start();

        try{
            FileInputStream fstream = new FileInputStream("C:\\Users\\icom942\\Desktop\\temp\\roman.txt");
            DataInputStream in = new DataInputStream(fstream);
            BufferedReader br = new BufferedReader(new InputStreamReader(in));
            String strLine;
            // int max = 0;
            String before = "";
            String after = "";
            while((strLine = br.readLine()) != null) {
                before += strLine;
                after += getAsRomanNumeral(parseRomanNumeral(strLine));
            }
            
            System.out.println("before: " + before.length());
            System.out.println("after: " + after.length());
            System.out.println("_____________________________");
            System.out.println("total saved: " + (before.length() - after.length()));
            
            in.close();
        } catch (Exception e){
            System.err.println("Error: " + e.getMessage());
        }
        sw.stop();
        System.out.println(sw);

    }
    
    private String getAsRomanNumeral(int numeral) {
        
        String romanNumeral = "";
        
        int thousands = (int) (Math.floor(numeral / 1000) * 1000);
        numeral -= thousands;
        
        int nineHundreds = (int) (Math.floor(numeral / 900) * 900);
        numeral -= nineHundreds;
        
        int fiveHundreds = (int) (Math.floor(numeral / 500) * 500);
        numeral -= fiveHundreds;
        
        int fourHundreds = (int) (Math.floor(numeral / 400) * 400);
        numeral -= fourHundreds;
        
        int oneHundreds = (int) (Math.floor(numeral / 100) * 100);
        numeral -= oneHundreds;
        
        int nineties = (int) (Math.floor(numeral / 90) * 90);
        numeral -= nineties;
        
        int fifties = (int) (Math.floor(numeral / 50) * 50);
        numeral -= fifties;
        
        int fourties = (int) (Math.floor(numeral / 40) * 40);
        numeral -= fourties;
        
        int tens = (int) (Math.floor(numeral / 10) * 10);
        numeral -= tens;
        
        int nines = (int) (Math.floor(numeral / 9) * 9);
        numeral -= nines;
        
        int fives = (int) (Math.floor(numeral / 5) * 5);
        numeral -= fives;
        
        int fours = (int) (Math.floor(numeral / 4) * 4);
        numeral -= fours;
        
        int ones = (int) (Math.floor(numeral / 1) * 1);
        numeral -= ones;
        
        for(int i = 1000; i <= thousands; i += 1000)
            romanNumeral += "M";
        
        for(int i = 900; i <= nineHundreds; i += 900)
            romanNumeral += "CM";
        
        for(int i = 500; i <= fiveHundreds; i += 500)
            romanNumeral += "D";
        
        for(int i = 400; i <= fourHundreds; i += 400)
            romanNumeral += "CD";
        
        for(int i = 100; i <= oneHundreds; i += 100)
            romanNumeral += "C";
        
        for(int i = 90; i <= nineties; i += 90)
            romanNumeral += "XC";
        
        for(int i = 50; i <= fifties; i += 50)
            romanNumeral += "L";
        
        for(int i = 40; i <= fourties; i += 40)
            romanNumeral += "XL";
        
        for(int i = 10; i <= tens; i += 10)
            romanNumeral += "X";
        
        for(int i = 9; i <= nines; i += 9)
            romanNumeral += "IX";
        
        for(int i = 5; i <= fives; i += 5)
            romanNumeral += "V";
        
        for(int i = 4; i <= fours; i += 4)
            romanNumeral += "IV";
        
        for(int i = 1; i <= ones; i += 1)
            romanNumeral += "I";
        
        return romanNumeral;
    }
    
    private int parseRomanNumeral(String romanNumeral) {
        
        String pattern = "IV";
        String updated = romanNumeral.replaceAll(pattern, "4 "); 
        
        pattern = "IX";
        updated = updated.replaceAll(pattern, "9 "); 
        
        pattern = "XL";
        updated = updated.replaceAll(pattern, "40 "); 
        
        pattern = "XC";
        updated = updated.replaceAll(pattern, "90 "); 
        
        pattern = "CD";
        updated = updated.replaceAll(pattern, "400 "); 
        
        pattern = "CM";
        updated = updated.replaceAll(pattern, "900 "); 
        
        pattern = "I";
        updated = updated.replaceAll(pattern, "1 "); 
        
        pattern = "V";
        updated = updated.replaceAll(pattern, "5 "); 
        
        pattern = "X";
        updated = updated.replaceAll(pattern, "10 "); 
        
        pattern = "L";
        updated = updated.replaceAll(pattern, "50 "); 
        
        pattern = "C";
        updated = updated.replaceAll(pattern, "100 "); 
        
        pattern = "D";
        updated = updated.replaceAll(pattern, "500 "); 
        
        pattern = "M";
        updated = updated.replaceAll(pattern, "1000 "); 
        
        String[] totalArr = updated.split(" ");
     
        int total = 0;
        for(String num : totalArr)
            total += Integer.parseInt(num);
        
        return total;
    }
}

