package net.projecteuler.problem25;

import java.math.BigInteger;

import org.apache.commons.lang.time.StopWatch;
import org.junit.Test;

public class Problem25 {

    @Test
    public void testTriangleNumbers() {
       
        BigInteger prevFib = BigInteger.valueOf(1L);
        BigInteger fib = BigInteger.valueOf(1L);
       
        StopWatch sw = new StopWatch();
        sw.start();
        int fibNum = 2;
        while(true) {
            BigInteger nextFib = prevFib.add(fib);
            prevFib = fib;
            fib = nextFib;
            ++fibNum;
            
            String nextFibDigits = nextFib.toString();
            
            if(nextFibDigits.length() == 1000) {
                System.out.println(fibNum);
                System.out.println(nextFibDigits);
                break;
            }
        }
        sw.stop();
        System.out.println(sw);
    }
} 