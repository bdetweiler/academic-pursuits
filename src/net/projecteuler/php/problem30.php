<?php

// 5 * 9 ^ 5 = 295245 = largest possible number in this set
$runningTotal = 0;
for($i = 2; $i < 295245; ++$i) {

    $numArr = str_split($i);

    $sum = 0;
    for($j = 0; $j < count($numArr); ++$j)
        $sum += pow($numArr[$j], 5);

    if($sum == $i) {
        echo "Found: $i\n";
        $runningTotal += $i;
    }
}

echo "Total: $runningTotal\n";
?>
