package com.net.projecteuler;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import org.apache.commons.lang.time.StopWatch;
import org.joda.time.DateTime;
import org.joda.time.DateTimeZone;
import org.junit.Ignore;
import org.junit.Test;

public class ProjectEuler {
    
    @Test
    public void testProb48() {
        String location = "DAL";
    
        /*
        for(Equipment equipment : equipmentList) {
            System.out.println(equipment);
            LOG.debug("equipment = " + equipment);
        }
        */
    }
    
    
 
    // Just for fun
    @SuppressWarnings("unused")
    private List<Long> getPrimeFactors(long n) {
        List<Long> factors = new ArrayList<Long>();
        if(n > 0)
            factors.add(1L);
        for(long i = 2; i <= n; i++) {
            while (n % i == 0) {
                factors.add(i);
                n /= i;
            }
        }
        // System.out.println(factors);
        // LOG.debug("primeFactors: " + factors);
        return factors;
    }
 
    // Just for fun
    public HashMap<Integer, Integer> findPrimes() {
        boolean[] arr = new boolean[1000000];
        
        // Initialize array
        for(int i = 0; i < arr.length; ++i)
            arr[i] = true;
     
        // Seive of Eratosthenes
        for(int i = 2; i < Math.sqrt(arr.length); ++i) {
            int k = 1;
            for(int j = (int)Math.pow(i, 2); j < arr.length; j = (int)(Math.pow(i, 2) + (k * i))) {
                arr[j] = false;
                ++k;
            }
        }
        
        HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
        
        int j = 1;
        for(int i = 2; i < arr.length; ++i) {
            // I'm doing something wrong in my seive, because it's not removing 6, so here's my hack
            if(arr[i] && i != 6) {
                map.put(Integer.parseInt(j + ""), i);
                ++j;
            }
        }
     
        return map;
     }
    
    // For fun
    @Ignore
    @Test
    public void testTriangleNumbers() {
      
        BigInteger bigInt = BigInteger.valueOf(2).pow(499);
        
        System.out.println(bigInt);
        
        long numberInSequence = 10;
        long triangleNum = 1;
        
        List<Long> primes = getPrimeFactors(triangleNum);
       
        StopWatch stopWatch = new StopWatch();
        stopWatch.start();
        for(long i = 10; i < numberInSequence; ++i) {
            triangleNum += i;
            
            primes = getPrimeFactors(triangleNum);
        
          
            List<Long> divisors = new ArrayList<Long>();
            divisors.add(1L);
            divisors.add(triangleNum);
            for(int j = 0; j < primes.size(); ++j) {
                for(int k = j + 1; k < primes.size(); ++k) {
                    if(!divisors.contains(primes.get(j) * primes.get(k)) && (primes.get(j) * primes.get(k)) <= triangleNum)
                        divisors.add(primes.get(j) * primes.get(k));
                }
            }
           
            if(divisors.size() > 75) {
                System.out.println("PRIMES: " + primes);
                System.out.println(i + "th Triangle Number: " + triangleNum + " has " + divisors.size() + " divisors: " + divisors);
            }
        }
        stopWatch.stop();
        
        System.out.println(stopWatch.toString());
        
    }
    

    // print N! permutation of the characters of the string s (in order)
    public void perm1(String s) { perm1("", s); }
    private void perm1(String prefix, String s) {
        int N = s.length();
        if (N == 0) System.out.println(prefix);
        else {
            for (int i = 0; i < N; i++)
               perm1(prefix + s.charAt(i), s.substring(0, i) + s.substring(i+1, N));
        }
    }
    
    public char[] rotate(char[] a) {
        char[] rval = new char[a.length];
      
        if(a.length <= 1)
            return a;
      
        for(int i = 0; i < (a.length - 1); ++i)
            rval[i] = a[i + 1];
        rval[a.length - 1] = a[0];
        return rval;
    }
    
    @Ignore
    @Test
    public void circularPrimeTest() {
      
        HashMap<Integer, Integer> map = findPrimes();
      
        long total = 0;
        
        for(int i = 2; i < 1000000; ++i) {
            
            if(!map.containsValue(i))
                continue;
            
            String s = "" + i;
           
            boolean successFlag = true;
            for(int j = 0; j < s.length() - 1; ++j) {
                s = new String(rotate(s.toCharArray()));
                Integer primeCandidate = Integer.parseInt(s);
                
                if(!map.containsValue(primeCandidate)) {
                    successFlag = false;
                    break;
                }
            }
            
            if(successFlag) {
                System.out.println("Cicular Prime: " + i);
                ++total;
            }
        }
        
        System.out.println("Total: " + total);
    }
    
    @Test
    public void dayOfMonthTest() {
        DateTime startDt = new DateTime(-2177452799999L, DateTimeZone.forID("GMT"));
        DateTime endDt = new DateTime(978220800001L, DateTimeZone.forID("GMT"));
      
        long sum = 0;
        while(startDt.isBefore(endDt)) {
            if(startDt.dayOfWeek().getAsText().equalsIgnoreCase("Sunday") && startDt.dayOfMonth().get() == 1)
                ++sum;
            startDt = startDt.plusDays(1);
        }
        
        System.out.println("Number of sundays: " + sum);
    }
    
    @Ignore
    @Test
    public void testBigInt() {
        BigInteger bigInt = BigInteger.valueOf(2).pow(1000);
        
        long sum = 0;
        for(char c : bigInt.toString().toCharArray())
            sum += Long.parseLong(c + "");
        
        System.out.println("sum = " + sum);
    }
   
    @Ignore
    @Test
    public void testPalindrome() { 
        StopWatch sw = new StopWatch();
        sw.start();
        long sum = 0;
        for(int i = 1; i < 1000000; ++i) {
            String num = new String(i + "");
            if(isPalindromic(num.toCharArray()) &&
               isPalindromic(Integer.toBinaryString(Integer.parseInt(num)).toCharArray()))
                sum += Long.parseLong(num);
        }
        sw.stop();
        System.out.println(sw.toString());
        System.out.println("Sum = " + sum);
    }
    
    public boolean isPalindromic(char[] arr) {
      
        for(int i = 0; i < Math.floor(arr.length / 2); ++i)
            if(arr[i] != arr[arr.length - i - 1])
                return false;
        
        return true;
    }
   
    @Test
    public void shiftPrime() {
        HashMap<Integer, Integer> map = findPrimes();
       
        Iterator<Entry<Integer, Integer>> it = map.entrySet().iterator();
        while(it.hasNext()) {
            Map.Entry<Integer, Integer> pairs = (Map.Entry<Integer, Integer>)it.next();
            Integer prime = pairs.getValue();
       
            boolean successFlag = true;
            while(prime > 0) {
                if(prime < 11)
                    break;
                prime = prime - Integer.valueOf((int)Math.floor(prime / Math.pow(10, ((new String(prime + "")).length() - 1))));
                if(!map.containsValue(prime)) {
                    successFlag = false;
                    break;
                }
            }
            
            if(successFlag)
                System.out.println("prime = " + prime);
                
            it.remove(); // avoids a ConcurrentModificationException
        }
    }
}
