package net.projecteuler.problem31;

import java.util.ArrayList;
import java.util.List;

import org.apache.commons.lang.time.StopWatch;
import org.junit.Test;

public class Problem31 {

    @Test
    public void testCombinations() {
     
        List<String> combs = new ArrayList<String>();
        int totalCombinations = 0;
        int[] comb = {0, 0, 0, 0, 0, 0, 0, 0};
        
        StopWatch sw = new StopWatch();
        sw.start();
        for(int twoPounds = 0; twoPounds <= 1; ++twoPounds) {
            comb[0] = twoPounds;
            for(int onePound = 0; onePound <= 2; ++onePound) {
                comb[1] = onePound;
                for(int fiftyPence = 0; fiftyPence <= 4; ++fiftyPence) {
                    comb[2] = fiftyPence;
                    for(int twentyPence = 0; twentyPence <= 10; ++twentyPence) {
                        comb[3] = twentyPence;
                        for(int tenPence = 0; tenPence <= 20; ++tenPence) {
                            comb[4] = tenPence;
                            for(int fivePence = 0; fivePence <= 40; ++fivePence) {
                                comb[5] = fivePence;
                                for(int twoPence = 0; twoPence <= 100; ++twoPence) {
                                    comb[6] = twoPence;
                                    for(int onePence = 0; onePence <= 200; ++onePence) {
                                        comb[7] = onePence;
                                        int total = comb[0] * 200;
                                        total += comb[1] * 100;
                                        total += comb[2] * 50;
                                        total += comb[3] * 20;
                                        total += comb[4] * 10;
                                        total += comb[5] * 5;
                                        total += comb[6] * 2;
                                        total += comb[7] * 1;
                                        if(total == 200) {
                                            ++totalCombinations;
                                            combs.add(comb[0] 
                                                     + " " 
                                                     + comb[1] 
                                                     + " " 
                                                     + comb[2] 
                                                     + " " 
                                                     + comb[3] 
                                                     + " " 
                                                     + comb[4]
                                                     + " "
                                                     + comb[5]
                                                     + " "
                                                     + comb[6]
                                                     + " "
                                                     + comb[7]
                                                     + " ");
                                        } else if(total > 200) {
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        sw.stop();
   
        for(String string : combs) {
            System.out.println(string);
        }
        System.out.println("time: " + sw);
        System.out.println(totalCombinations);
    }
} 