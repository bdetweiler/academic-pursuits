<?php

/**
 * File:    problem62.php
 * Author:  Brian Detweiler
 */

include_once("EulerUtils.php");

$EulerUtils = new EulerUtils();
$start = microtime(true);

$min = 1;
$max = 2000;
$powersArr = array();
for($i = $min; $i < $max; ++$i)
    array_push($powersArr, pow($i, 3));

for($i = 0; $i < count($powersArr); ++$i) {
    $total = 1;
    for($j = $i + 1; $j < count($powersArr); ++$j) {

        if($EulerUtils->isPermutation($powersArr[$i], $powersArr[$j])) {
            echo $powersArr[$i] . " is a permutaiton of " . $powersArr[$j] . "\n";
            ++$total;
        }
    }

    if($total == 5)
        echo "Found it: $powersArr[$i]\n";
}

echo "Time: " . (microtime(true) - $start) . "\n";
