<?php
/**
 * File:    problem39.php
 * Author:  Brian Detweiler
 */
include_once('EulerUtils.php');
$EulerUtils = new EulerUtils();

$timeStart = microtime(true);


$max = 0;
$myFile = "/home/bdetweiler/src/projecteuler/pandigital_primes.txt";
$handle = @fopen($myFile, "r");
while (($prime = fgets($handle, 4096)) !== false) {
    $one = 0;
    $two = 0;
    $three = 0;
    $four = 0;
    $five = 0;
    $six = 0;
    $seven = 0;

    $primeArr = str_split($prime);

    for($i = 0; $i < count($primeArr); ++$i) {
        if($primeArr[$i] == 0)
            continue;
        if($primeArr[$i] == 1)
            ++$one;
        else if($primeArr[$i] == 2)
            ++$two;
        else if($primeArr[$i] == 3)
            ++$three;
        else if($primeArr[$i] == 4)
            ++$four;
        else if($primeArr[$i] == 5)
            ++$five;
        else if($primeArr[$i] == 6)
            ++$six;
        else if($primeArr[$i] == 7)
            ++$seven;
    }

    if($one == 1 &&
       $two == 1 &&
       $three == 1 &&
       $four == 1 &&
       $five == 1 &&
       $six == 1 &&
       $seven == 1) {
        if($prime > $max)
            $max = $prime;
    }
}
fclose($handle);

$timeEnd = microtime(true);

echo "max = $max\n";
echo ($timeEnd - $timeStart) . "\n";

?>
