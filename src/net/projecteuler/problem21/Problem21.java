package net.projecteuler.problem21;

import java.util.ArrayList;
import java.util.List;

import net.projecteuler.utils.EulerUtils;

import org.junit.Test;

public class Problem21 {

    @Test
    public void testAmicablePairs() {
        List<Long> amicablePairs = new ArrayList<Long>();
        for(long a = 220; a < 10000; ++a) {
            long b = d(a);
            if(b != a && d(b) == a)
                amicablePairs.add(a);
        }
        
        long sum = 0L;
        for(Long l : amicablePairs)
            sum += l;
        
        System.out.println(sum);
    }
    
    private long d(long n) {
        List<Long> divisors = EulerUtils.getDivisors(Long.valueOf(n), true);
        long sum = 0L;
        for(Long div : divisors)
            if(div != n)
                sum += div.longValue();
        return sum;
    }
} 