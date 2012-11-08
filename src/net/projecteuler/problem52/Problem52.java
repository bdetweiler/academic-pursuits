package net.projecteuler.problem52;

import java.util.Arrays;

import org.apache.commons.lang.time.StopWatch;
import org.junit.Test;


public class Problem52 {

    @Test
    public void testProblem52() {
        
        StopWatch sw = new StopWatch();
        sw.start();
        for(int i = 1; true; ++i) {
            // Initial number for comparison
            char[] oneTimes = (i + "").toCharArray();
            Arrays.sort(oneTimes);
           
            // Start high so we can short circuit
            char[] sixTimes = ((6 * i) + "").toCharArray();
            Arrays.sort(sixTimes);
            
            if(!Arrays.equals(oneTimes, sixTimes))
                continue;
            
            char[] fiveTimes = ((5 * i) + "").toCharArray();
            Arrays.sort(fiveTimes);
            
            if(!Arrays.equals(oneTimes, fiveTimes))
                continue;
            
            char[] fourTimes = ((4 * i) + "").toCharArray();
            Arrays.sort(fourTimes);
            
            if(!Arrays.equals(oneTimes, fourTimes))
                continue;
            
            char[] threeTimes = ((3 * i) + "").toCharArray();
            Arrays.sort(threeTimes);
            
            if(!Arrays.equals(oneTimes, threeTimes))
                continue;
            
            char[] twoTimes = ((2 * i) + "").toCharArray();
            Arrays.sort(twoTimes);
            
            if(!Arrays.equals(oneTimes, twoTimes))
                continue;
            
            System.out.println("Winner: " + i);
            break;
        }
        sw.stop();
        System.out.println(sw);
    }
}