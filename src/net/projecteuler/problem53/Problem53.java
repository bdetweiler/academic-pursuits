package net.projecteuler.problem53;

import java.math.BigInteger;

import net.projecteuler.utils.EulerUtils;

import org.apache.commons.lang.time.StopWatch;
import org.junit.Test;


public class Problem53 {

    @Test
    public void testProblem52() {
      
        int limit = 100;
       
        BigInteger n = BigInteger.valueOf(23L);
        BigInteger r = BigInteger.valueOf(10L);
        
        StopWatch sw = new StopWatch();
        sw.start();
      
        int count = 0;
        for(int i = 1; i <= limit; ++i) {
            for(int j = 1; j <= i; ++j) { 
                n = BigInteger.valueOf(i);
                r = BigInteger.valueOf(j);
                BigInteger c = EulerUtils.comb(n, r);
                
                if(c.longValue() > 1000000L) {
                    ++count;
                    System.out.println(count + " for " + n + " choose " + r + ": " + c);
                }
                
            }
        }
        sw.stop();
        System.out.println(sw);
    }
}