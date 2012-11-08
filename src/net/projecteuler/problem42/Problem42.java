package net.projecteuler.problem42;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import org.junit.Test;

public class Problem42 {
    
    @Test
    public void testTriangleWords() {
        try{
            FileInputStream fstream = new FileInputStream("C:\\Users\\icom942\\Desktop\\temp\\names.txt");
            DataInputStream in = new DataInputStream(fstream);
            BufferedReader br = new BufferedReader(new InputStreamReader(in));
            String strLine;
          
            List<Integer> triNums = new ArrayList<Integer>();
          
            // Keep list of first 26 triangle numbers
            triNums.add(1);
            triNums.add(3);
            triNums.add(6);
            triNums.add(10);
            triNums.add(15);
            triNums.add(21);
            triNums.add(28);
            triNums.add(36);
            triNums.add(45);
            triNums.add(55);
            triNums.add(66);
            triNums.add(78);
            triNums.add(91);
            triNums.add(105);
            triNums.add(120);
            triNums.add(136);
            triNums.add(153);
            triNums.add(171);
            triNums.add(190);
            triNums.add(210);
            triNums.add(231);
            triNums.add(253);
            triNums.add(276);
            triNums.add(300);
            triNums.add(325);
            triNums.add(351);
           
            List<String> triangleWords = new ArrayList<String>();
            // int max = 0;
            while((strLine = br.readLine()) != null) {
                
                // if(max < strLine.length())
                    // max = strLine.length();
                int triangleWord = 0;
                for(char c : strLine.toCharArray()) {
                    triangleWord += (c - 64);
                }
                if(triNums.contains(Integer.valueOf(triangleWord)))
                    triangleWords.add(strLine);
            }
           
            System.out.println(triangleWords.size() + " triangle words: " + triangleWords);
            // System.out.println("Max: " + max);
            in.close();
        } catch (Exception e){
            System.err.println("Error: " + e.getMessage());
        }
    }
}