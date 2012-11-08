package net.projecteuler.problem92;

import org.apache.commons.lang.time.StopWatch;
import org.junit.Test;


public class Problem92 {

    @Test
    public void testChains() {
        
        StopWatch sw = new StopWatch();
        sw.start();
    
        long eightyNines = 0L;
        long ones = 0L;
        for(long seed = 1L; seed < 10000000; ++seed) {

            long newSeed = seed;
            while(newSeed != 1 && newSeed != 89) {
                char[] seedArr = (new String(newSeed + "")).toCharArray();
           
                long sum = 0;
                for(int j = 0; j < seedArr.length; ++j) {
                    long digit = (long) Math.pow(Long.parseLong("" + seedArr[j]), 2L);
                    sum += digit;
                }
                newSeed = sum;
            }
          
            if(newSeed == 89) {
                ++eightyNines;
            } else {
                ++ones;
            }
        }
        
        sw.stop();
        System.out.println("ones = " + ones);
        System.out.println("eightyNines = " + eightyNines);
        System.out.println(sw);

    }
    
}