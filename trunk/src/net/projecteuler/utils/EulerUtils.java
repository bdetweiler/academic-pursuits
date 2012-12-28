package net.projecteuler.utils;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import org.apache.commons.lang.time.StopWatch;

public class EulerUtils {
    
    public static final String PERFECT = "PERFECT";
    
    public static final String DEFICIENT = "DEFICIENT";
    
    public static final String ABUNDANT = "ABUNDANT";
   
    public static HashMap<Integer, Integer> seive(int size) {
        
        StopWatch sw = new StopWatch();
        sw.start();
        
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
        
        sw.split();
            
        HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
            
        int j = 1;
        for(int i = 2; i < arr.length; ++i) {
            if(arr[i]) {
                map.put(Integer.parseInt(j + ""), i);
                ++j;
            }
        }
        
        sw.stop();
        
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
        
    public static List<Long> getPrimeFactors(long n) {
        
        List<Long> factors = new ArrayList<Long>();
        
        for(long i = 2; i <= n; i++) {
            while (n % i == 0) {
                factors.add(i);
                n /= i;
            }
        }
        return factors;
    }
    
    public static boolean isPrime(long n) {
       
        List<Long> factors = getPrimeFactors(n);
        
        if(factors.size() == 1)
            return true;
        
        return false;
    }
    
    public static List<Long> getDivisors(Long n, boolean sort) {
        
        List<Long> divisors = getPrimeFactors(n);
       
        if(n > 1 && !divisors.contains(n))
            divisors.add(n);
        
        // for(long i = 2; i < (n / 2) + 1; ++i)
        for(long i = 2; i < (n / 2) + 1; ++i)
            if(n % i == 0 && !divisors.contains(i))
                divisors.add(i);
        
        if(sort)
            Collections.sort(divisors);
       
        return new ArrayList<Long>(new HashSet<Long>(divisors));
    }
  
    public static BigInteger factorial(int n) {
        BigInteger rval = BigInteger.ONE;
        for(int i = 1; i <= n; ++i)
            rval = rval.multiply(BigInteger.valueOf(i));
        return rval;
    }

    /**
     * triangleNumber
     * --
     * Triangle Number formula is [(n(n + 1)) / 2]
     * @param n
     * @return
     */
    public static BigInteger triangleNumber(long n) {
        BigInteger rval = BigInteger.valueOf(n);
        rval = rval.multiply(BigInteger.valueOf(n + 1L));
        return rval.divide(BigInteger.valueOf(2L));
    }
    
    /**
     * pentagonalNumber
     * --
     * Pn = ((3 * (n ^ 2)) - n) / 2
     * @param n
     * @return
     */
    public static BigInteger pentagonalNumber(long n) {
        BigInteger rval = BigInteger.valueOf(n);
        return BigInteger.valueOf(3).multiply(rval.pow(2)).subtract(rval).divide(BigInteger.valueOf(2));
    }
    
    public static boolean isPentagonal(long n) {
        double[] quad = quadratic(3, -1, -(n * 2));
       
        double root1 = quad[0];
        double root2 = quad[1];
       
        // Test first root
        String[] root1Arr = (new String(root1 + "")).split("\\.");
        
        Long decimal = 0L;
        
        if(root1Arr.length > 1)
            decimal = Long.parseLong(root1Arr[1]);
        
        if(decimal == 0)
            return true;
       
        // Test second root
        String[] root2Arr = (new String(root2 + "")).split("\\.");
        
        decimal = 0L;
        
        if(root2Arr.length > 1)
            decimal = Long.parseLong(root2Arr[1]);
        
        if(decimal == 0)
            return true;
        
        return false;
    }
  
    /**
     * quadratic
     * --
     * Quadratics come in the form of 
     *     aX^2 + bY + Z
     *     
     * @param a
     * @param b
     * @param Z
     * @return
     */
    public static double[] quadratic(double a, double b, double c) {
        
        
        //Finding out the roots
        double sqroot = Math.sqrt(b * b - 4 * a * c);
 
        double root1 = (-b +  sqroot) / (2*a) ;
        double root2 = (-b -  sqroot) / (2*a) ;

        double[] rval = {root1, root2};
       
        return rval;
    }
   
    /**
     * numberOfDivisors
     * --
     * Returns the number of divisors of n
     * @param n
     * @return
     */
    public static int numberOfDivisors(int n) {
        int count = 0;
        int sqr = (int) Math.sqrt(n);
        
        for(int i = 1; i <= sqr; ++i)
            if(n % i == 0)
                ++count;
        
        count *= 2;
        
        if(sqr * sqr == n)
            --count;
        
        return count;
    }
    
    public static String perfectAbundantDeficient(long n) {
        List<Long> divisors = getDivisors(n, false);
        long sum = 0;
        for(Long num : divisors)
            sum += num;
       
        if(n > 1)
            sum -= n;
       
        if(sum == n)
            return PERFECT;
        else if(sum > n)
            return ABUNDANT;
        else
            return DEFICIENT;
    }
    
    public static boolean isPerfect(long n) {
        return perfectAbundantDeficient(n).equalsIgnoreCase(PERFECT) ? true : false;
    }
    
    public static boolean isAbundant(long n) {
        return perfectAbundantDeficient(n).equalsIgnoreCase(ABUNDANT) ? true : false;
    }
    
    public static boolean isDeficient(long n) {
        return perfectAbundantDeficient(n).equalsIgnoreCase(DEFICIENT) ? true : false;
    }
   
    /**
     * getDistinctPrimeFactors
     * --
     * Returns distinct prime factors (if the prime factors are 2 * 2 * 3 * 5 it will return 4, 3, 5)
     * So basically, if there are multiple primes of the same number, it will just raise them to their power
     * @param n
     * @return
     */
    public static List<Long> getDistinctPrimeFactors(Long n) {
        Map<Long, Long> map = new HashMap<Long, Long>();
            
        List<Long> distinctPrimeFacotrs = getPrimeFactors(n);
        for(Long l : distinctPrimeFacotrs) {
            Long j = 1L;
            if(map.containsKey(l))
                j = map.get(l) + 1;
            map.put(l, j);
        }
        distinctPrimeFacotrs.clear();
        
        Iterator<Entry<Long, Long>> it = map.entrySet().iterator();
        while(it.hasNext()) {
            @SuppressWarnings("rawtypes")
            Map.Entry pairs = it.next();
            distinctPrimeFacotrs.add((long)Math.pow(Double.parseDouble(pairs.getKey() + ""), Double.parseDouble(pairs.getValue() + "")));
            it.remove();
        }
        
        return distinctPrimeFacotrs;
    }
    
    public static BigInteger comb(BigInteger n, BigInteger r) {
       return factorial(n).divide(factorial(r).multiply(factorial((n.subtract(r)))));
    }
    
    public static BigInteger factorial(BigInteger n) {
        if(n.equals(BigInteger.ZERO))
            return BigInteger.ONE;
        
        return n.multiply(factorial(n.subtract(BigInteger.ONE)));
    }
    
    public static boolean isPerfectSquare(Long n) {
        String [] numArr = (new String(Math.sqrt(n) + "")).split("\\.");
        
        Long decimal = 0L;
        
        if(numArr.length > 1)
            decimal = Long.parseLong(numArr[1]);
        
        return decimal == 0L;
    }
}