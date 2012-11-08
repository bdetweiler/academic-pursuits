package net.projecteuler.problem60;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;

import net.projecteuler.utils.EulerUtils;

import org.apache.commons.lang.time.StopWatch;
import org.junit.Test;


public class Problem60 {

    // TODO
    
    @Test
    public void testProblem60() {
        
        StopWatch sw = new StopWatch();
        sw.start();
  
        List<Integer> primesList = EulerUtils.seiveList(10000);
        List<Integer> primesList1 = primesList;
        
        List<Integer> winnersList = new ArrayList<Integer>();
      
        for(Integer prime : primesList) {
            for(Integer test : primesList1) {
                if(primesList.contains(Integer.parseInt("" + prime + test)) &&
                   primesList.contains(Integer.parseInt("" + test + prime))) {
                   winnersList.add(test);
                   winnersList.add(prime);
                }
            }
        }
     
        winnersList = new ArrayList<Integer>(new HashSet<Integer>(winnersList));
        Collections.sort(winnersList);

        primesList = winnersList;
        primesList1 = winnersList;
      
        
        System.out.println(winnersList);

        
        sw.stop();
        System.out.println(sw);

    }

}

