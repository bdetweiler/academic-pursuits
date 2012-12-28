<?php

$names = file_get_contents("/home/bdetweiler/src/projecteuler/names1.txt");

$namesArr = explode(",", $names);

sort($namesArr);

print_r($namesArr);

$total = 0;
for($i = 0; $i < count($namesArr); ++$i) {

    $name = str_split($namesArr[$i]);

    $nameTotal = 0;
    for($j = 0; $j < count($name); ++$j) {

        if(ord($name[$j]) > 64)
            $nameTotal += ord($name[$j]) - 64;
        else
            echo " NOT PRINTING THIS FUCKER: " . $name[$j] . "\n";
    }
    
    $total += $nameTotal * ($i + 1);

}
echo "Total = $total\n";
// print_r($namesArr);

?>
