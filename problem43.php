<?php
/**
 * File:    problem43.php
 * Author:  Brian Detweiler
 */
include_once('EulerUtils.php');
$EulerUtils = new EulerUtils();
$sum = 0;


$timeStart = microtime(true);

$pandigitalArr = $EulerUtils->permute("123456789");
for($i = 0; $i < count($pandigitalArr); ++$i) {
    $numberArr = str_split($pandigitalArr[$i]);

    $number1 = $numberArr[0] . "0" . $numberArr[1] . $numberArr[2] . $numberArr[3] . $numberArr[4] . $numberArr[5] . $numberArr[6] . $numberArr[7] . $numberArr[8];
    $number2 = $numberArr[0] . $numberArr[1] . "0" . $numberArr[2] . $numberArr[3] . $numberArr[4] . $numberArr[5] . $numberArr[6] . $numberArr[7] . $numberArr[8];
    $number3 = $numberArr[0] . $numberArr[1] . $numberArr[2] . "0" . $numberArr[3] . $numberArr[4] . $numberArr[5] . $numberArr[6] . $numberArr[7] . $numberArr[8];
    $number4 = $numberArr[0] . $numberArr[1] . $numberArr[2] . $numberArr[3] . "0" . $numberArr[4] . $numberArr[5] . $numberArr[6] . $numberArr[7] . $numberArr[8];
    $number5 = $numberArr[0] . $numberArr[1] . $numberArr[2] . $numberArr[3] . $numberArr[4] . "0" . $numberArr[5] . $numberArr[6] . $numberArr[7] . $numberArr[8];
    $number6 = $numberArr[0] . $numberArr[1] . $numberArr[2] . $numberArr[3] . $numberArr[4] . $numberArr[5] . "0" . $numberArr[6] . $numberArr[7] . $numberArr[8];
    $number7 = $numberArr[0] . $numberArr[1] . $numberArr[2] . $numberArr[3] . $numberArr[4] . $numberArr[5] . $numberArr[6] . "0" . $numberArr[7] . $numberArr[8];
    $number8 = $numberArr[0] . $numberArr[1] . $numberArr[2] . $numberArr[3] . $numberArr[4] . $numberArr[5] . $numberArr[6] . $numberArr[7] . "0" . $numberArr[8];
    $number9 = $numberArr[0] . $numberArr[1] . $numberArr[2] . $numberArr[3] . $numberArr[4] . $numberArr[5] . $numberArr[6] . $numberArr[7] . $numberArr[8] . "0";
    
    $pandigitalNumberArr = array();
    array_push($pandigitalNumberArr, $number1);
    array_push($pandigitalNumberArr, $number2);
    array_push($pandigitalNumberArr, $number3);
    array_push($pandigitalNumberArr, $number4);
    array_push($pandigitalNumberArr, $number5);
    array_push($pandigitalNumberArr, $number6);
    array_push($pandigitalNumberArr, $number7);
    array_push($pandigitalNumberArr, $number8);
    array_push($pandigitalNumberArr, $number9);

    for($j = 0; $j < count($pandigitalNumberArr); ++$j) {
        if(substr($pandigitalNumberArr[$j], 1, 3) % 2 == 0 &&
           substr($pandigitalNumberArr[$j], 2, 3) % 3 == 0 &&
           substr($pandigitalNumberArr[$j], 3, 3) % 5 == 0 &&
           substr($pandigitalNumberArr[$j], 4, 3) % 7 == 0 &&
           substr($pandigitalNumberArr[$j], 5, 3) % 11 == 0 &&
           substr($pandigitalNumberArr[$j], 6, 3) % 13 == 0 &&
           substr($pandigitalNumberArr[$j], 7, 3) % 17 == 0) {
            echo "$pandigitalNumberArr[$j] is a winner!\n";
            $sum += $pandigitalNumberArr[$j];
        }
    }
} 

$timeEnd = microtime(true);

echo "sum = $sum\n";
echo ($timeEnd - $timeStart) . "\n";

?>
