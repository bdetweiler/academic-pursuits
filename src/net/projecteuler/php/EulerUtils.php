<?php

class EulerUtils {

    /**
     * Constructor
     * --
     */
    function __construct() {
        ;;;
    }

    /**
     * findPrimes
     * --
     * Finds primes up to a given number n using the Seive of Eratosthenes
     */
    public function findPrimes($n)
    {
        $nlist = array();
        $sqrt = ceil(sqrt($n));

        $nlist[] = 2;
        $nlist[] = 3;
        for($i = 5; $i < $n; $i = $i + 2) {
            if($i%3 != 0)
                $nlist[] = $i;
        }
        
        for($i = 2, $divisor = 5; $divisor < $sqrt ; ++$i) {
           /*
            * Remove non primes numbers from an array ($nlist)
            * Non prime numbers are identified by dividing with a known
            * prime (the prime n in our array at $index)
            */
            $count = count($nlist);
            $j = $i * $i;
            $nlist2 = array_slice($nlist, 0, $j);
            
            for(; $j < $count; $j++) {
                $num = $nlist[$j];
                if($num % $divisor != 0)
                    $nlist2[] = $num;
            }

            unset($nlist);
            $nlist = $nlist2;
            $divisor = $nlist[$i + 1];
        }
        
        return $nlist;
    }

    /**
     * getPrimeFactors
     * --
     * Get all prime factors of the number
     */
    public function getPrimeFactors($num) {

        $factors = array();
        if($num == 1)
            return;

        $root = ceil(sqrt($num)) + 1;
        $i = 2;
        while($i <= $root) {
            if($num % $i == 0) {
                $factors[] = $i;
                $num /= $i;
                return true;
            }
            ++$i;
        }
        $factors[] = $num;
        return $factors;
    }


    /**
     * isPrime
     * --
     * Returns true/false if n is prime or not
     */
    public function isPrime($n) {
        if($n < 2)
            return false;

        for($i = 2; $i <= ($n / 2); ++$i)
            if($n % $i == 0)
                return false;

        return true;

    }

    /**
     * isFloat
     * --
     * Lots of times it's nice to know if we're dealing with a float
     * such as in the case of determining roots
     */
    public function isFloat($n) {

        $candidateArr = explode(".", $n);

        return (count($candidateArr) != 1);
    }

    /**
     * pythag
     * --
     * Returns the pythagorean theorem answer for sides a and b.
     */
    public function pythag($a, $b) {
        return sqrt(pow($a, 2) + pow($b, 2));
    }

    /**
     * calculateAngleSSS
     * --
     * Calculates angle C of triangle with sides c, a, b of known lengths. 
     */
    public function calculateAngleSSS($c, $a, $b) {
        $angleInRadians = acos((pow($a, 2) + pow($b, 2) - pow($c, 2)) / (2 * $a * $b));
        return rad2deg($angleInRadians);
    }

    /**
     * getTriangleNumber
     * --
     * Returns the nth triangle number
     */
    public function getTriangleNumber($n) {
        return ($n * ($n + 1)) / 2;
    }

    /**
     * getPentagonalNumber
     * --
     * Returns the nth pentagonal number
     */
    public function getPentagonalNumber($n) {
        return ((3 * pow($n, 2)) - $n) / 2;
    }

    /**
     * getHexagonalNumber
     * --
     * Returns the nth hexagonal number
     */
    public function getHexagonalNumber($n) {
        return (2 * pow($n, 2)) - $n;
    }

    /**
     * isTriangleNumber
     * --
     * Given a number, determine if it is a triangle number and return its position in the series
     * The quadratic equation is:
     *     (x ^ 2) + x - (2 * n) = 0
     *     where n is our candidate
     */
    public function isTriangleNumber($n) {

        $candidates = $this->quadratic(1, 1, -($n * 2), 'both');

        $candidateArr = explode(",", $candidates);

        foreach($candidateArr as $value) {
            // Turn it into a number, not a string
            $value *= 1;
            if(is_int($value) && $value > 0)
                return $value;
        }
    
        return 0;
    }

    /**
     * isHexagonalNumber
     * --
     * Given a number, determine if it is a hexagonal number and return its position in the series
     * The quadratic equation is:
     *     2 * (x ^ 2) - x - n = 0
     *     where n is our candidate
     */
    public function isHexagonalNumber($n) {

        $candidates = $this->quadratic(2, -1, -$n, 'both');

        $candidateArr = explode(",", $candidates);

        // print_r($candidateArr);
        foreach($candidateArr as $value) {
            // Turn it into a number, not a string
            $value *= 1;
            if(is_int($value) && $value > 0)
                return $value;
        }
    
        return 0;
    }

    /**
     * isPentagonalNumber
     * --
     * Given a number, determine if it is a pentagonal number and return its position in the series
     * The quadratic equation is:
     *     3 * (x ^ 2) - x - (2 * n) = 0
     *     where n is our candidate
     */
    public function isPentagonalNumber($n) {

        $candidates = $this->quadratic(3, -1, -($n * 2), 'both');

        $candidateArr = explode(",", $candidates);

        // print_r($candidateArr);

        foreach($candidateArr as $value) {
            // Turn it into a number, not a string
            $value *= 1;
            if(is_int($value) && $value > 0)
                return $value;
        }
    
        return 0;
    }

    public function isPermutation($str1, $str2) {
        $str1Arr = str_split($str1);
        $str2Arr = str_split($str2);

        sort($str1Arr);
        sort($str2Arr);

        return (count($str1Arr) == count($str2Arr)) && (implode($str1Arr) == implode($str2Arr));
    }

    public function isPalindrome($str) {
        $strArr = str_split($str);
       
        for($i = 0; $i <= floor(count($strArr) / 2); ++$i)
            if($strArr[$i] != $strArr[count($strArr) - $i - 1])
                return false;

        return true;
    }

    /**
     * permute
     * --
     * Returns an array of all permutations of a string
     */
    public function permute($str) {
        if(strlen($str) < 2)
            return array($str);

        $permutations = array();

        $tail = substr($str, 1);

        foreach($this->permute($tail) as $permutation) {
            $length = strlen($permutation);

            for($i = 0; $i <= $length; $i++)
                $permutations[] = substr($permutation, 0, $i) . $str[0] . substr($permutation, $i);
        }

        return array_unique($permutations);
    }


    /**
    * Quadratic Solver Function for PHP
    *
    * Useage: for 3x^2 + 4x + 5 = 0, use quadratic(3, 4, 5, 'root1') and quadratic(3, 4, 5, 'root2'),
    * or simply just quadratic(3, 4, 5, 'both').
    * The $root argument doesn't define which value it will be in relation to the other - I could
    * easily have called them John and Jane, instead of 1st and 2nd.
    *
    * @author Gary Jones
    * @link http://code.garyjones.co.uk/quadratic-solver-function-php/
    * @since 2004-03-21
    * @version 2011-01-01
    *
    * @param integer $a
    * @param integer $b
    * @param integer $c
    * @param string $root 'root1', 'root2' or 'both. Default is 'both'
    * @param integer $precision Number of decimal place rounding. Default is 3
    * @return mixed The root value
    */
    function quadratic($a, $b, $c, $root = 'both', $precision = 3) {
       
        $bsmfac = $b * $b - 4 * $a * $c;
     
        // Accounts for complex roots.
        if($bsmfac < 0) {
            $plusminusone = ' + ';
            $plusminustwo = ' - ';
            $bsmfac *= - 1;
            $complex = (sqrt( $bsmfac ) / (2 * $a));
     
            // if negative imaginary term, tidies appearance.
            if($a < 0) {
                $plusminustwo = ' + ';
                $plusminusone = ' - ';
                $complex *= - 1;
            }

            $lambdaone = round( -$b / (2 * $a), $precision ) . $plusminusone . round( $complex, $precision ) . 'i';
            $lambdatwo = round( -$b / (2 * $a), $precision ) . $plusminustwo . round( $complex, $precision ) . 'i';
        }
     
        // Simplifies if b^2 = 4ac (real roots).
        else if($bsmfac == 0) {
            $lambdaone = round( -$b / (2 * $a), $precision );
            $lambdatwo = round( -$b / (2 * $a), $precision );
        }
        else { // Finds real roots when b^2 != 4ac.
            $lambdaone = (-$b + sqrt( $bsmfac )) / (2 * $a);
            $lambdaone = round( $lambdaone, $precision );
            $lambdatwo = (-$b - sqrt( $bsmfac )) / (2 * $a);
            $lambdatwo = round( $lambdatwo, $precision );
        }

        // Return what is asked for.
        if('root1' == $root)
            return $lambdaone;
        if('root2' == $root)
            return $lambdatwo;
        if('both' == $root)
            return $lambdaone. ',' . $lambdatwo;
    }
}
?>
