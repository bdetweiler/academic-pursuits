package com.codeeval.email_regex;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.regex.Pattern;

public class email_regex {

    public static void main (String[] args) throws NumberFormatException, IOException {
        File file = new File(args[0]);
        BufferedReader in = new BufferedReader(new FileReader(file));
        String line;
        while ((line = in.readLine()) != null) {
            emailValid(line);
        }
        
        System.exit(0);
      }

    public static void emailValid(String email) {
        email = email.toLowerCase();
        // Pattern p = Pattern.compile("[a-z0-9\\.!#\\$%&'*+-/=\\?\\^_`{|}~]*@[a-z\-");
    }
} 