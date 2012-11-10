<?php

$handle = @fopen("/home/bdetweiler/src/projecteuler/primes49.txt", "r");

$primes = "";
while(($buffer = fgets($handle, 4096)) !== false)
    $primes .= $buffer;
fclose($handle);

$primesArr = explode(" ", $primes);

for($i = 0; $i < count($primesArr); ++$i) {
    // Permute the string
    $primePermutedArr = permute($primesArr[$i]);

    $sequence = array();
    array_push($sequence, $primesArr[$i]);
    for($j = 0; $j < count($primePermutedArr); ++$j) {
        if(trim($primePermutedArr[$j]) != "" && preg_match("/$primePermutedArr[$j]/", $primes) && $primePermutedArr[$j] != $primesArr[$i])
            array_push($sequence, $primePermutedArr[$j]);
    }

    sort($sequence);
    // $sequence = array_reverse($sequence);
    $candidate = $sequence;

    $differenceArr = array();

    $winnerFlag = true;

    if(count($sequence) > 2) {
        for($j = 0; $j < count($sequence); ++$j)
            for($k = $j + 1; $k < count($sequence); ++$k) {
                $diff = $sequence[$k] - $sequence[$j];
                $differenceArr[$diff] += 1;

                if($differenceArr[$sequence[$k] - $sequence[$j]] >= 2 && $diff == 3330) {
                    print_r($sequence);
                    
                }
                
            }
    }


    
}
    



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

    return array_unique($permutations);
}

?>
