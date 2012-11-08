package net.projecteuler.problem45;

import org.junit.Test;


public class Problem45 {
    
    @Test
    public void testPrime() {
        
        for(long i = 1L; i < 1000000; ++i)
            if(t(i) == p(i) && t(i) == h(i))
                System.out.println(i);
        
    }
    
    private long t(long n) {
        return (n * (n + 1)) / 2;
    }
    
    private long p(long n) {
        return (n * (3 * n - 1)) / 2;
    }
    
    private long h(long n) {
        return (n * (2 * n - 1));
    }
}