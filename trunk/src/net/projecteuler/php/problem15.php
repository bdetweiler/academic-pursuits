<?php
/**
 * File:    problem24.php
 * Author:  Brian Detweiler
 */
$arr = permute("RRRRRDDDDD");

$arr = array_unique($arr);

print_r($arr);

echo "count = " . count($arr) . "\n";


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
