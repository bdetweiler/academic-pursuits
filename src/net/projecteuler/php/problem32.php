<?php
/**
 * File:    problem32.php
 * Author:  Brian Detweiler
 */

$str = "123456789";

/* Bounds:
 *   * there are no XXX * XXX pandigital products
 *   * there are no XX * XX pandigital products
 *   * XXX * YY == YY * XXX so we can just look at only YY * XXX products
 */

// 362880 permutations
$permutations = permute($str);

$winners = array();
$productWinners = array();
$sum = 0;

for($i = 0; $i < count($permutations); ++$i) {

    $candidateArr = str_split($permutations[$i]);

    // XX * YYY = ZZZZ
    $multiplicand = $candidateArr[0] . $candidateArr[1];
    $multiplier = $candidateArr[2] . $candidateArr[3] . $candidateArr[4];
    $product = $candidateArr[5] . $candidateArr[6] . $candidateArr[7] . $candidateArr[8];

    if(($multiplicand * $multiplier) == $product) {
        echo "FOUND ONE! $permutations[$i]\n";
        echo $multiplicand . " * " . $multiplier . " (" . ($multiplicand * $multiplier) . ") == " . $product . "\n";
        array_push($winners, $permutations[$i]);
    }
}

print_r($winners);

$final = array();

for($i = 0; $i < count($winners); ++$i) {
    $winner = str_split($winners[$i]);

    $str = $winner[5] . $winner[6] . $winner[7] . $winner[8];
    array_push($final, $str);
}

$final = array_unique($final);

print_r($final);

/**
 * 
 */
function permute($str) {
    if(strlen($str) < 2)
        return array($str);

    $permutations = array();

    $tail = substr($str, 1);

    foreach(permute($tail) as $permutation) {
        $length = strlen($permutation);

        for($i = 0; $i <= $length; $i++)
            $permutations[] = substr($permutation, 0, $i) . $str[0] . substr($permutation, $i);
    }

    return $permutations;
}

?>
