package net.projecteuler.problem23;

import net.projecteuler.utils.EulerUtils;

import org.apache.commons.lang.time.StopWatch;
import org.junit.Test;

public class Problem23 {

    @Test
    public void testAbundantNumbers() {
        short lLimit = 0;
        short uLimit = 28122;
        long sum = 0;
        long sumOfAllNumbers = 0;
    
        boolean[] abundantArr = new boolean[uLimit];
        
        
        StopWatch sw = new StopWatch();
        sw.start();
       
        // Populate a hash of all abundant numbers
        for(short i = lLimit; i < uLimit; ++i) {
            if(EulerUtils.isAbundant(i))
                abundantArr[i] = true;
            else 
                abundantArr[i] = false;
            
            // Sum the set of all numbers within the bounds
            sumOfAllNumbers += i;
        }
            
        // Go over all numbers and check below them to find composits
        for(short i = (short)(lLimit + lLimit); i < uLimit; ++i) {
            
            for(short j = lLimit; j < i; ++j) {
                if(!abundantArr[j])
                    continue;
                
                if(abundantArr[i - j]) {
                    sum += i;
                    break;
                }
            }
        }
        
        sw.stop();
       
        System.out.println("Sum = " + (sumOfAllNumbers - sum));
        System.out.println(sw);
    }
} 