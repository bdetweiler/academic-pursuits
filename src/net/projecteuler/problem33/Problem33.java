package net.projecteuler.problem33;

import org.junit.Test;

public class Problem33 {

    @Test
    public void testFractions() {
                
        Double answerNum = 1.0;
        Double answerDen = 1.0;

        for(double den = 11; den <= 99; ++den) {
            for(double num = 10; num < den; ++num) {
               
                char[] numArr = (new String(num + "")).toCharArray();
                char[] denArr = (new String(den + "")).toCharArray();
               
                Double num0 = Double.parseDouble(numArr[0] + "");
                Double num1 = Double.parseDouble(numArr[1] + "");
                
                Double den0 = Double.parseDouble(denArr[0] + "");
                Double den1 = Double.parseDouble(denArr[1] + "");
               
                if((num % 10 == 0) && (den % 10) == 0)
                    continue;
                
                if(numArr[0] == denArr[0] && den1 != 0) {
                    if((num1 / den1) == (num / den)) {
                        answerNum *= num;
                        answerDen *= den;
                        System.out.println(num + " / " + den + " = " + (num / den));
                    }
                }
                if(numArr[1] == denArr[1] && den0 != 0) {
                    if((num0 / den0) == (num / den)) {
                        answerNum *= num;
                        answerDen *= den;
                        System.out.println(num + " / " + den + " = " + (num / den));
                    }
                }
                if(numArr[1] == denArr[0] && den1 != 0) {
                    if((num0 / den1) == (num / den)) {
                        answerNum *= num;
                        answerDen *= den;
                        System.out.println(num + " / " + den + " = " + (num / den));
                    }
                }
                if(numArr[0] == denArr[1] && den0 != 0) {
                    if((num1 / den0) == (num / den)) {
                        answerNum *= num;
                        answerDen *= den;
                        System.out.println(num + " / " + den + " = " + (num / den));
                    }
                }
            }
        }
        
        System.out.println(answerNum + " / " + answerDen + " = " + (answerNum / answerDen));
    }
}   