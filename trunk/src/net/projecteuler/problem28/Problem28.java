package net.projecteuler.problem28;

import org.junit.Test;


public class Problem28 {

    char[] directions = {'R', 'D', 'L', 'U'};
    
    @Test
    public void buildSpiral() {
        int n = 1001;
        int start = (int) Math.floor(n/2);
  
        int level = 1;
        int direction = 0;
        int j = start;
        int k = start;
        int runningNumber = 1;
       
        int[][] spiral = new int[n][n];
       
        // Starting position
        spiral[j][k] = 1;
        
        while(level < n) {
           
            for(int rdlu = 0; rdlu < 2; ++rdlu) {
                switch(directions[direction]) {
                    case 'R':
                        for(int m = 0; m < level; ++m) {
                            ++k;
                            spiral[j][k] = ++runningNumber;
                        }
                        break;
                    case 'D':
                        for(int m = 0; m < level; ++m) {
                            ++j;
                            spiral[j][k] = ++runningNumber;
                        }
                        break;
                    case 'L':
                        for(int m = 0; m < level; ++m) {
                            --k;
                            spiral[j][k] = ++runningNumber;
                        }
                        break;
                    case 'U':
                        for(int m = 0; m < level; ++m) {
                            --j;
                            spiral[j][k] = ++runningNumber;
                        }
                        break;
                }
                direction = (direction + 1) % 4;
            }
            
            ++level;
        }
       
        // Get the last row
        for(int m = 0; m < (n - 1); ++m) {
            ++k;
            spiral[0][k] = ++runningNumber;
        }
        
        int total = addDiags(spiral, n);
        System.out.println(spiral);
        System.out.println("total = " + total);
    }
    
    private int addDiags(int[][] arr, int n) {
        int rval = 1;
        
        int j = (int) Math.floor(n/2);
        int k = (int) Math.floor(n/2);
        
        //Right Down
        while(j < (n - 1) && k < (n - 1))
            rval += arr[++j][++k];
        
        j = (int) Math.floor(n/2);
        k = (int) Math.floor(n/2);
            
        //Right Up
        while(j > 0 && k < (n - 1))
            rval += arr[--j][++k];
        
        j = (int) Math.floor(n/2);
        k = (int) Math.floor(n/2);
        
        //Left Down
        while(j < (n - 1) && k > 0)
            rval += arr[++j][--k];
        
        j = (int) Math.floor(n/2);
        k = (int) Math.floor(n/2);
        
        //Left Up
        while(j > 0 && k > 0)
            rval += arr[--j][--k];
        
        return rval;
    }
}
