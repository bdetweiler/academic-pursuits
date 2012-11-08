package net.projecteuler.problem55;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

import org.apache.commons.lang.time.StopWatch;
import org.junit.Test;


public class Problem55 {

    @Test
    public void testProblem55() {
        
        StopWatch sw = new StopWatch();
        sw.start();
    
        List<BigInteger> nonLychrelNumbers = new ArrayList<BigInteger>();
        List<BigInteger> lychrelNumbers = new ArrayList<BigInteger>();
        for(int i = 0; i < 10000; ++i) {
            BigInteger lychrelCandidate = BigInteger.valueOf(i);
            
            List<BigInteger> temp = new ArrayList<BigInteger>();
            for(int j = 0; j <= 50; ++j) {
                lychrelCandidate = lychrelCandidate.add(getReverse(lychrelCandidate));
                temp.add(lychrelCandidate);
                if(isPalindrome(lychrelCandidate + "") || nonLychrelNumbers.contains(lychrelCandidate)) {
                    nonLychrelNumbers.addAll(temp);
                    break;
                }
        
                if(j == 50)
                    lychrelNumbers.add(BigInteger.valueOf(i));
            }
        }
        
        System.out.println(lychrelNumbers.size() + " lychrel numbers");
        sw.stop();
        System.out.println(sw);

    }

    private BigInteger getReverse(BigInteger number) {
        
        char[] numArr = (new String(number + "")).toCharArray();
     
        String reversedNumber = "";
        for(int i = numArr.length - 1; i >= 0; --i)
            reversedNumber += numArr[i];
        
        return new BigInteger(reversedNumber);
    }
    
    private boolean isPalindrome(String number) {
       
        char[] numberArr = number.toCharArray();
        // If it's even
        if(number.length() % 2 == 0) {
            for(int i = 0; i < number.length(); ++i)
                if(numberArr[i] != numberArr[number.length() - i - 1])
                    return false;
        } else
            for(int i = 0; i < (number.length() - 1); ++i)
                if(numberArr[i] != numberArr[number.length() - i - 1])
                    return false;
       
        return true;
    }
}

