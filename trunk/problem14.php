<?php

/**
 * Found value 837799 - took 258 seconds. 
 * 70600674
 */

$numberList = array();

$start = microtime(true);
$knownChains = array();

$max = 0;
for($i = 2; $i < 1000000; ++$i) {
    
    $term = $i;

    $tmp = 0;
    $arr = array($term);
    while($term > 1) {

        $term = nextTerm($term);

        if(isset($knownChains[$term])) {
            $tmp = $knownChains[$term];
            break;
        }

        array_push($arr, $term);
    }

    $knownChains[$i] = count($arr) + $tmp;

    if($knownChains[$i] > $max) {

        // print_r($arr);
        $max = $knownChains[$i];
        echo "Term: $i\n";
    }


}

echo "Time: " . (microtime(true) - $start) . "\n";


function nextTerm($num) {
    if($num % 2 == 0)
        return $num / 2;
    else
        return (3 * $num) + 1;
}

?>
