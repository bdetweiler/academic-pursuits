package net.projecteuler.problem139;

import net.projecteuler.utils.EulerUtils;

import org.apache.commons.lang.time.StopWatch;
import org.junit.Test;

public class Problem139 {

    @Test
    public void testPythagTrips() {
      
        StopWatch sw = new StopWatch();
        sw.start();
        int count = 0;
        for(int i = 1; i < 10; ++i) {
            // int[] triplet = EulerUtils.stifelPythagoreanTriplets(i);
            int[] triplet = EulerUtils.euclidPythagoreanTriplets(i);
            
            int bigSquare = triplet[2];
            int littleSquare = triplet[1] - triplet[0];
            if(bigSquare == 0 || littleSquare == 0)
                continue;
           
            System.out.println("trip: (" + triplet[0] + ", " + triplet[1] + ", " + triplet[2] + ")");
            if(bigSquare % littleSquare == 0) {
                ++count;
                System.out.println("Winner: (" + triplet[0] + ", " + triplet[1] + ", " + triplet[2] + ")");
            }
        }
        sw.stop();
        System.out.println("count = " + count);
        System.out.println(sw);
    }
} 