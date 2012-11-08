package com.codeeval.fizzbuzz;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class fizzbuzz {

    public static void main (String[] args) throws NumberFormatException, IOException {
        File file = new File(args[0]);
        BufferedReader in = new BufferedReader(new FileReader(file));
        String line;
        while ((line = in.readLine()) != null) {
            String[] lineArray = line.split("\\s");
            playFizzBuzz(Integer.parseInt(lineArray[0]), Integer.parseInt(lineArray[1]), Integer.parseInt(lineArray[2]));
        }
        
        System.exit(0);
      }

    public static void playFizzBuzz(int fizz, int buzz, int limit) {
        for(int i = 1; i <= limit;) {
            if(i % fizz == 0 && i % buzz == 0)
                System.out.print("FB");
            else if(i % fizz == 0)
                System.out.print("F");
            else if(i % buzz == 0)
                System.out.print("B");
            else
                System.out.print(i);
            
            if(++i > limit)
                break;
           
            System.out.print(" ");
        }
        System.out.println();
    }
} 