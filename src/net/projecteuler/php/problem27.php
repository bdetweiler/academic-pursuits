<?php
/**
 * File:    problem27.php
 * Author:  Brian Detweiler
 */

include_once("EulerUtils.php");

$runningTotal = 0;
$triangleNumbers = array();
for($i = 1; $i <= 1000; ++$i) {
    $runningTotal += $i;
    array_push($triangleNumbers, $runningTotal);
}

$EulerUtils = new EulerUtils();


$time_start = microtime();


$limit = 1000;

// Overall max
$max  = 0;
$maxA = 0;
$maxB = 0;

// Get the product of the one that produces the overall max
$maxProduct = 0;

for($a = 1; $a < $limit; ++$a) {
    for($b = 1; $b < $limit; ++$b) {

        $plusPlusMax   = 0;
        $plusMinusMax  = 0;
        $minusPlusMax  = 0;
        $minusMinusMax = 0;

        $plusPlus   = true;
        $plusMinus  = true;
        $minusPlus  = true;
        $minusMinus = true;

        $n = 0;
        while($plusPlus || $plusMinus || $minusPlus || $minusMinus) {

            if($plusPlus) {
                $candidate = pow($n, 2) + ($a * $n) + $b;
                if(!$EulerUtils->isPrime($candidate))
                    $plusPlus = false;
                else {
                    ++$plusPlusMax;
                    if($plusPlusMax > $max) {
                        $max = $plusPlusMax;
                        $maxProduct = $a * $b;
                        $maxA = $a;
                        $maxB = $b;
                        echo "$a X $b = new max ($max)\n";
                    }
                }
            }


            if($plusMinus) {
                $candidate = pow($n, 2) - ($a * $n) + $b;
                if(!$EulerUtils->isPrime($candidate))
                    $plusMinus = false;
                else {
                    ++$plusMinusMax;
                    if($plusMinusMax > $max) {
                        $max = $plusMinusMax;
                        $maxProduct = $a * -$b;
                        $maxA = $a;
                        $maxB = $b;
                        echo "$a X $b = new max ($max)\n";
                    }
                }
            }

            if($minusPlus) {
                $candidate = pow($n, 2) + ($a * $n) - $b;
                if(!$EulerUtils->isPrime($candidate))
                    $minusPlus = false;
                else {
                    ++$minusPlusMax;
                    if($minusPlusMax > $max) {
                        $max = $minusPlusMax;
                        $maxProduct = -$a * $b;
                        $maxA = $a;
                        $maxB = $b;
                        echo "$a X $b = new max ($max)\n";
                    }
                }
            }

            if($minusMinus) {
                $candidate = pow($n, 2) - ($a * $n) - $b;
                if(!$EulerUtils->isPrime($candidate))
                    $minusMinus = false;
                else {
                    ++$minusMinusMax;
                    if($minusMinusMax > $max) {
                        $max = $minusMinusMax;
                        $maxProduct = -$a * -$b;
                        $maxA = $a;
                        $maxB = $b;
                        echo "$a X $b = new max ($max)\n";
                    }
                }
            }

            ++$n;
        }
    }
}

$time_end = microtime();
$time = $time_end - $time_start;

echo "Found it! $max: $maxProduct\n";
echo "$time\n";

?>
