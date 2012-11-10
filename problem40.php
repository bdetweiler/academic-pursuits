<?php
/**
 * File:    problem39.php
 * Author:  Brian Detweiler
 */

$max = 0;
$limit = 1000;

$time_start = microtime(true);

$myFile = "/home/bdetweiler/src/projecteuler/numbers.txt";
$fh = fopen($myFile, 'w') or die("can't open file");

// Write the string to a file
for($i = 0; $i < 200000; ++$i)
    fwrite($fh, $i);

fclose($fh);

// Read the file back in and break it into an array
$myFile = "/home/bdetweiler/src/projecteuler/numbers.txt";
$fh = fopen($myFile, 'r');
$theData = fread($fh, 1088890);
fclose($fh);

$numbersArr = str_split($theData);

$d1 = $numbersArr[1];
$d10 = $numbersArr[10];
$d100 = $numbersArr[100];
$d1000 = $numbersArr[1000];
$d10000 = $numbersArr[10000];
$d100000 = $numbersArr[100000];
$d1000000 = $numbersArr[1000000];

echo "d100 x d1000 x d10000 x d100000 x d1000000 = " . ($d1 * $d10 * $d100 * $d1000 * $d10000 * $d100000 * $d1000000) . "\n";

$time_end = microtime(true);
$time = $time_end - $time_start;

echo "$time\n";
?>
