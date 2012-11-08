package net.projecteuler.problem29;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

import org.apache.commons.lang.time.StopWatch;
import org.junit.Test;

public class Problem29 {

    @Test
    public void testCombinations() {
    
        StopWatch sw = new StopWatch();
        sw.start();
        List<BigInteger> combinations = new ArrayList<BigInteger>();
        for(int i = 2; i <= 100; ++i)
            for(int j = 2; j <= 100; ++j) {

                BigInteger candidate = power(i, j);
                if(!combinations.contains(candidate))
                    combinations.add(candidate);
            }
       
        System.out.println("answer: " + combinations.size());
        sw.stop();
        
        System.out.println(sw.toString());
    }
    
    private BigInteger power(long value, long power) {
       
       BigInteger runningTotal = BigInteger.valueOf(value);
       BigInteger multipliedAgainst = BigInteger.valueOf(value);
       
       for(int i = 1; i < power; ++i)
           runningTotal = runningTotal.multiply(multipliedAgainst);
      
       return runningTotal;
    }
} 