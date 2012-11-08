package net.projecteuler.problem34;

import net.projecteuler.utils.EulerUtils;

import org.apache.commons.lang.time.StopWatch;
import org.junit.Test;

public class Problem34 {

    @Test
    public void testCuriousNumbers() {
        StopWatch sw = new StopWatch();
        sw.start();
        long sum = 0;
        for(long i = 3; i < 100000L; ++i) {
            char[] num = (new String(i + "")).toCharArray();
            
            long total = 0;
            for(int j = 0; j < num.length; ++j)
                total += EulerUtils.factorial(Integer.parseInt("" + num[j])).longValue();
            
            if(total == i)
                sum += i;
        }
        sw.stop();
        System.out.println(sum);
        System.out.println(sw);
    }
}   