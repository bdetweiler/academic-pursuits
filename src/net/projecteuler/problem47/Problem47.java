package net.projecteuler.problem47;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import net.projecteuler.utils.EulerUtils;

import org.apache.commons.lang.time.StopWatch;
import org.junit.Test;
import org.junit.runner.notification.StoppedByUserException;


public class Problem47 {
    
    @Test
    public void testTwo() {
        int limit = 2;
        for(long i = 2; i < 100; ++i) {
            List<Long> allPrimeFactors = new ArrayList<Long>();
            List<Long> reducedPrimeFactors = new ArrayList<Long>();
            
            List<Long> distinctPrimeFactors1 = EulerUtils.getDistinctPrimeFactors(i);
            if(distinctPrimeFactors1.size() != limit)
                continue;
            allPrimeFactors.addAll(distinctPrimeFactors1);
            
            List<Long> distinctPrimeFactors2 = EulerUtils.getDistinctPrimeFactors(i + 1);
            if(distinctPrimeFactors2.size() != limit)
                continue;
            allPrimeFactors.addAll(distinctPrimeFactors2);
       
            
            reducedPrimeFactors = new ArrayList<Long>(new HashSet<Long>(allPrimeFactors));
            
            if(reducedPrimeFactors.size() == (limit * limit)) {
                System.out.println("Winners are " + i + " and " + (i + 1));
                break;
            }
        }
    }
    
    @Test
    public void testThree() {
        int limit = 3;
        for(long i = 2; i < 1000; ++i) {
            List<Long> allPrimeFactors = new ArrayList<Long>();
            List<Long> reducedPrimeFactors = new ArrayList<Long>();
            
            List<Long> distinctPrimeFactors1 = EulerUtils.getDistinctPrimeFactors(i);
            if(distinctPrimeFactors1.size() != limit)
                continue;
            allPrimeFactors.addAll(distinctPrimeFactors1);
            
            List<Long> distinctPrimeFactors2 = EulerUtils.getDistinctPrimeFactors(i + 1);
            if(distinctPrimeFactors2.size() != limit) {
                ++i;
                continue;
            }
            allPrimeFactors.addAll(distinctPrimeFactors2);
       
            List<Long> distinctPrimeFactors3 = EulerUtils.getDistinctPrimeFactors(i + 2);
            if(distinctPrimeFactors3.size() != limit) {
                ++i;
                ++i;
                continue;
            }
            allPrimeFactors.addAll(distinctPrimeFactors3);
        
            
            reducedPrimeFactors = new ArrayList<Long>(new HashSet<Long>(allPrimeFactors));
            
            if(reducedPrimeFactors.size() == (limit * limit)) {
                System.out.println("Winners are " + i + " and " + (i + 1) + " and " + (i + 2));
                break;
            }
        }
    }
    
    @Test
    public void testFour() {
        StopWatch sw = new StopWatch();
        sw.start();
        int limit = 4;
        for(long i = 644; i < 1000000; ++i) {
            List<Long> allPrimeFactors = new ArrayList<Long>();
            List<Long> reducedPrimeFactors = new ArrayList<Long>();
            
            List<Long> distinctPrimeFactors1 = EulerUtils.getDistinctPrimeFactors(i);
            if(distinctPrimeFactors1.size() != limit)
                continue;
            allPrimeFactors.addAll(distinctPrimeFactors1);
            
            List<Long> distinctPrimeFactors2 = EulerUtils.getDistinctPrimeFactors(i + 1);
            if(distinctPrimeFactors2.size() != limit) {
                ++i;
                continue;
            }
            allPrimeFactors.addAll(distinctPrimeFactors2);
       
            List<Long> distinctPrimeFactors3 = EulerUtils.getDistinctPrimeFactors(i + 2);
            if(distinctPrimeFactors3.size() != limit) {
                ++i;
                ++i;
                continue;
            }
            allPrimeFactors.addAll(distinctPrimeFactors3);
        
            List<Long> distinctPrimeFactors4 = EulerUtils.getDistinctPrimeFactors(i + 3);
            if(distinctPrimeFactors4.size() != limit) {
                ++i;
                ++i;
                ++i;
                continue;
            }
            allPrimeFactors.addAll(distinctPrimeFactors4);
            
            reducedPrimeFactors = new ArrayList<Long>(new HashSet<Long>(allPrimeFactors));
            
            if(reducedPrimeFactors.size() == (limit * limit)) {
                System.out.println("Winners are " + i + " and " + (i + 1) + " and " + (i + 2) + " and " + (i + 3));
                break;
            }
        }
        sw.stop();
        System.out.println(sw);
    }
}