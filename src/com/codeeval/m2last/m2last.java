package com.codeeval.m2last;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class m2last {

    public static void main (String[] args) throws NumberFormatException, IOException {
        File file = new File(args[0]);
        BufferedReader in = new BufferedReader(new FileReader(file));
        String line;
        while ((line = in.readLine()) != null) {
            String[] lineArray = line.split("\\s");
            Integer m = Integer.parseInt(lineArray[lineArray.length - 1]);
            if(m >= lineArray.length)
                continue;
            System.out.println(lineArray[lineArray.length - 1 - m]);
        }
        
        System.exit(0);
    }
} 