package lcs;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class lcs {

    public static void main (String[] args) throws NumberFormatException, IOException {
        File file = new File(args[0]);
        BufferedReader in = new BufferedReader(new FileReader(file));
        String line;
        while ((line = in.readLine()) != null) {
            if(line.trim().equalsIgnoreCase(""))
                continue;
            String[] stringsArr = line.split(";");
            getLcs(stringsArr[0], stringsArr[1]);
        }
        
        System.exit(0);
      }

    public static void getLcs(String s1, String s2) {
       
        List<String> answers = new ArrayList<String>();
        
        char[] s1Arr = s1.toCharArray();
        char[] s2Arr = s2.toCharArray();
        
        // Attempt matching substrings in s1 to s2 for each possibility
        for(int i = 0; i < s1Arr.length; ++i) {
            String s = "";
            // Starting position advances by 1 each time
            int kPos = 0;
            for(int j = i; j < s1Arr.length; ++j) {
                
                for(int k = kPos; k < s2Arr.length; ++k) {
                    if(s1Arr[j] == s2Arr[k]) {
                        s += s1Arr[j];
                        answers.add(s);
                        ++k;
                        kPos = k;
                        break;
                    }
                }
                
                if(kPos == s2Arr.length)
                    break;
            }
        }
        
        // Attempt matching substrings in s1 to s2 for each possibility
        for(int i = 0; i < s2Arr.length; ++i) {
            String s = "";
            // Starting position advances by 1 each time
            int kPos = 0;
            for(int j = i; j < s2Arr.length; ++j) {
                
                for(int k = kPos; k < s1Arr.length; ++k) {
                    if(s2Arr[j] == s1Arr[k]) {
                        s += s2Arr[j];
                        System.out.println(s);
                        answers.add(s);
                        ++k;
                        kPos = k;
                        break;
                    }
                }
                
                if(kPos == s2Arr.length)
                    break;
            }
        }
        
        System.out.println(answers);
        int max = 0;
        int i = 0;
        int indexAnswer = 0;
        for(String answer : answers) {
            if(answer.length() > max) {
                max = answer.length();
                indexAnswer = i;
            } 
            ++i;
        }
        
        System.out.println(answers.get(indexAnswer));
    }
} 