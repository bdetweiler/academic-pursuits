package net.projecteuler.problem12;

import java.math.BigInteger;
import java.util.List;

import net.projecteuler.utils.EulerUtils;

import org.apache.commons.lang.time.StopWatch;
import org.junit.Test;

public class Problem12 {

    @Test
    public void testTriangleNumbers() {
       
        long startNumberInSequence = 2079;
        long numberInSequence = 100000000;
        BigInteger triangleNum = BigInteger.ONE;
       
        long max = 0;
        
        StopWatch sw = new StopWatch();
        sw.start();
        
        for(long n = startNumberInSequence; n < numberInSequence; ++n) {
            triangleNum = EulerUtils.triangleNumber(n);
         
            List<Long> divisors = EulerUtils.getDivisors(triangleNum.longValue(), true);
            
            if(divisors.size() > max) {
                max = divisors.size();
                System.out.println("sequence number " + n + " (" + triangleNum + ") has " + max + " divisors!");
                System.out.println(divisors);
            }
            
            if(max > 500) {
                break;
            }
        }
        
        sw.stop();
        System.out.println(sw);
    }
} 