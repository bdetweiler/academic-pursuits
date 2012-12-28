<?php

include_once('EulerUtils.php');
$EulerUtils = new EulerUtils();
$timeStart = microtime(true);

$p = permute("12345678");

$max = 0;
for($i = 0; $i < count($p); ++$i) { 
    echo "permuation = $p[$i]\n";
    if($EulerUtils->isPrime($p[$i]))
        if($p[$i] > $max)
            $max = $p[$i];
}

$timeEnd = microtime(true);

echo "max = $max\n";
echo ($timeEnd - $timeStart) . "\n";
    



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

    print_r($permutations);

    return $permutations;
}

?>
