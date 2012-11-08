package net.projecteuler.problem50;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import net.projecteuler.utils.EulerUtils;

import org.apache.commons.lang.time.StopWatch;
import org.junit.Ignore;
import org.junit.Test;


public class Problem50 {
    
    @Test
    public void testPrimeBetter() {
        StopWatch sw = new StopWatch();
        int uLimit = 1000000;
        int max = 0;
        List<Integer> primes = EulerUtils.seiveList(uLimit);
        Collections.sort(primes);
        List<Integer> tmp1 = new ArrayList<Integer>(primes);
        List<Integer> tmp2 = new ArrayList<Integer>(primes);
      
        List<Integer> testList = new ArrayList<Integer>();
        
        sw.start();
        // The prime we are starting from
        for(Integer startPrime : tmp1) {
            // The sum of the sequence
            int sum = 0;
            // The number of elements in the sequence
            int count = 0;
            
            for(Integer sequencePrime : tmp2) {
                
                if(sequencePrime < startPrime)
                    continue;
                
                ++count;
                sum += sequencePrime;
                
                if(sum > uLimit)
                    break;
                
                if(EulerUtils.isPrime(sum)) {
                    if(count > max) {
                        max = count;
                        System.out.println("New winner: " + sum + " with " + count + " elements");
                    }
                }
                    
            }
        }
        sw.stop();
        System.out.println(sw);
    }
    
    @Ignore
    @Test
    public void testPrime() {
        StopWatch sw = new StopWatch();
        int uLimit = 1000000;
        int lLimit = 800000;
        int max = 0;
        int winner = 0;
        List<Integer> primes = EulerUtils.seiveList(uLimit);
        Collections.sort(primes);
        List<Integer> tmp1 = new ArrayList<Integer>(primes);
        List<Integer> tmp2 = new ArrayList<Integer>(primes);
      
        sw.start();
        // The prime we are trying to add up to
        for(Integer testPrime : primes) {
            
            if(testPrime < lLimit)
                continue;
            
            boolean skipWork = false;
           
            // The prime we are going to start looking for a sequence at
            for(Integer startPrime : tmp1) {
                // The sum of the sequence
                int sum = 0;
                // The number of elements in the sequence
                int count = 0;
                
                if(startPrime > testPrime)
                    break;
              
                List<Integer> testList = new ArrayList<Integer>();
                
                // The sequence between startPrime and testPrime
                for(Integer sequencePrime : tmp2) {
                    if(sequencePrime < startPrime)
                        continue;
              
                    testList.add(sequencePrime);
                        
                    ++count;
                    sum += sequencePrime;
                   
                    if(sum > testPrime)
                        break;
                    
                    // Found a winner
                    if(sum == testPrime) {
                        if(count > max) {
                            max = count;
                            winner = testPrime;
                            System.out.println("============NEW max = " + max);
                            System.out.println("winner = " + winner);
                            System.out.println(testPrime);
                            System.out.println("count = " + count);
                            System.out.println("max = " + max);
                            System.out.println(testList);
                        }
                        skipWork = true;
                        
                        break;
                    }
                }
               
                if(skipWork)
                    break;
            }
            
        }
        
        sw.stop();
        System.out.println(sw);
    }
    
}