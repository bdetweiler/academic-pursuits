package com.codeeval.double_squares;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

public class double_squares {
    public static void main(String[] args) throws IOException {
        File file = new File(args[0]);
        BufferedReader in = new BufferedReader(new FileReader(file));
        String line;

        while ((line = in.readLine()) != null) {
            int count = 0;
            Integer num = Integer.parseInt(line);
            List<String> used = new ArrayList<String>();

            List<Integer> primes = new ArrayList<Integer>();
            primes.add(0);
            primes.add(1);

            List<Integer> primesList = seiveList(num);

            primes.addAll(primesList);

            for (Integer prime : primes) {
                if (prime > Math.sqrt(num))
                    break;

                long square = (long) Math.pow(prime, 2);
                Long remainder = (long) (num - square);

                if (isPerfectSquare(remainder) && !used.contains(square + "," + remainder) && !used.contains(remainder + "," + square)) {
                    ++count;
                    used.add(square + "," + remainder);
                    used.add(remainder + "," + square);
                }

            }

            System.out.println(count);
        }
    }

    public static boolean isPerfectSquare(Long n) {
        String[] numArr = (new String(Math.sqrt(n) + "")).split("\\.");

        Long decimal = 0L;

        if (numArr.length > 1)
            decimal = Long.parseLong(numArr[1]);

        return decimal == 0L;
    }

    public static HashMap<Integer, Integer> seive(int size) {

        boolean[] arr = new boolean[size];

        for (int i = 0; i < arr.length; ++i)
            arr[i] = true;

        // Seive of Eratosthenes
        for (int i = 2; i < Math.sqrt(arr.length); ++i) {
            int k = 0;
            for (int j = (int) Math.pow(i, 2); j < arr.length; j = (int) (Math.pow(i, 2) + (k * i))) {
                arr[j] = false;
                ++k;
            }
        }

        HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();

        int j = 1;
        for (int i = 2; i < arr.length; ++i) {
            if (arr[i]) {
                map.put(Integer.parseInt(j + ""), i);
                ++j;
            }
        }

        return map;
    }

    public static List<Integer> seiveList(int n) {
        List<Integer> rval = new ArrayList<Integer>();
        Map<Integer, Integer> map = seive(n);

        @SuppressWarnings("rawtypes")
        Iterator it = map.entrySet().iterator();
        while (it.hasNext()) {
            @SuppressWarnings("rawtypes")
            Map.Entry pairs = (Map.Entry) it.next();
            rval.add((Integer) pairs.getValue());
            it.remove();
        }

        return rval;
    }
}