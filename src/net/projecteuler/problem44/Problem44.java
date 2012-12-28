package net.projecteuler.problem44;

import net.projecteuler.utils.EulerUtils;

import org.junit.Test;

public class Problem44 {
    
    @Test
    public void testPentagonal() { 
       
        int limit = 10000;
        long min = 50000000;
        int minI = 50000000;
        int minJ = 50000000;
        long minPentI = 50000000;
        long minPentJ = 50000000;
    
        for(int i = 1; i < limit; ++i) {
            for(int j = i + 1; j < limit && (j - i) < 5000; ++j) {
                long pentI = EulerUtils.pentagonalNumber(i).longValue();
                long pentJ = EulerUtils.pentagonalNumber(j).longValue();
                if(EulerUtils.isPentagonal(pentI + pentJ) && EulerUtils.isPentagonal(Math.abs(pentI - pentJ))) {
                    System.out.println(pentI + ", " + pentJ + ", " + (pentI + pentJ) + ", " + (pentJ - pentI));
                    if(Math.abs(pentI - pentJ) < min) {
                        min = pentJ - pentI;
                        minI = i;
                        minJ = j;
                        minPentI = pentI;
                        minPentJ = pentJ;
                    }
                }
            }
        }
        
        System.out.println("min = " + min);
        System.out.println("minPentI = " + minPentI);
        System.out.println("minPentJ = " + minPentJ);
        System.out.println("minI = " + minI);
        System.out.println("minJ = " + minJ);
    }
}