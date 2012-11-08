package com.codeeval.primenumbers;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

public class PrimeNumbers {

    public static void main (String[] args) throws NumberFormatException, IOException {
        File file = new File(args[0]);
        BufferedReader in = new BufferedReader(new FileReader(file));
        String line;
        while ((line = in.readLine()) != null) {
            String[] lineArray = line.split("\\s");
                for(int i = 0; i < lineArray.length; ++i)
                    testPrimeNumber(Integer.parseInt(lineArray[i]));
        }
        
        System.exit(0);
      }
    
    private static void testPrimeNumber(int n) {
       
        List<Integer> primes = seiveList(n);
        Collections.sort(primes);
    
        String solution = "";
        for(Integer i : primes)
            solution += i + ",";
       
        // Remove final comma
        solution = solution.substring(0, solution.length() - 1);
        
        System.out.println(solution);
    }
    
    public static HashMap<Integer, Integer> seive(int size) {
        
        boolean[] arr = new boolean[size];
             
        for(int i = 0; i < arr.length; ++i)
            arr[i] = true;
          
        // Seive of Eratosthenes
        for(int i = 2; i < Math.sqrt(arr.length); ++i) {
            int k = 0;
            for(int j = (int)Math.pow(i, 2); j < arr.length; j = (int)(Math.pow(i, 2) + (k * i))) {
                arr[j] = false;
                ++k;
           }
        }
        
        HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
            
        int j = 1;
        for(int i = 2; i < arr.length; ++i) {
            if(arr[i]) {
                map.put(Integer.parseInt(j + ""), i);
                ++j;
            }
        }
        
        return map;
    }
    
    public static List<Integer> seiveList(int n) {
        List<Integer> rval = new ArrayList<Integer>();
        Map<Integer, Integer> map = seive(n);
        
        @SuppressWarnings("rawtypes")
        Iterator it = map.entrySet().iterator();
        while(it.hasNext()) {
            @SuppressWarnings("rawtypes")
            Map.Entry pairs = (Map.Entry)it.next();
            rval.add((Integer) pairs.getValue());
            it.remove();
        }
        
        return rval;
    }
} 