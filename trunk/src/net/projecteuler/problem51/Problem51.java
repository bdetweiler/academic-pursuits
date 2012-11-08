package net.projecteuler.problem51;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import net.projecteuler.utils.EulerUtils;

import org.junit.Test;


public class Problem51 {
    
    @Test
    public void testPrime() {
        HashMap<Integer, Integer> primes = EulerUtils.seive(2000);
        
        @SuppressWarnings("rawtypes")
        Iterator it = primes.entrySet().iterator();
        while(it.hasNext()) {
            @SuppressWarnings("rawtypes")
            Map.Entry pairs = (Map.Entry)it.next();
            @SuppressWarnings("unused")
            String prime = pairs.getValue() + "";
            
            System.out.println(pairs.getKey() + " = " + pairs.getValue());
            it.remove();
        }
        
        
    }
}