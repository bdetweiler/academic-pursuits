<?php

/**
 * File:    problem59.php
 * Author:  Brian Detweiler
 */
$start = microtime(true);

$handle = @fopen("/home/bdetweiler/src/projecteuler/cipher1.txt", "r");
$buffer = fgets($handle, 3203);

$messageArr = explode(",", $buffer);

for($i = ord("a"); $i <= ord("z"); ++$i) {
    for($j = ord("a"); $j <= ord("z"); ++$j) {
        for($k = ord("a"); $k <= ord("z"); ++$k) {
            $key = array();
            array_push($key, $i);
            array_push($key, $j);
            array_push($key, $k);

            $message = "";
            $skip = false;
            $total = 0;
            for($n = 0; $n < count($messageArr); ++$n) {
                $character = $messageArr[$n] ^ $key[$n % 3];

                $total += $character;
                if($character > ord("z") || $character < ord(" ")) {
                    $skip = true;
                    break;
                }

                $message .= chr($character);
            }
            if($skip)
                continue;

            echo "key = " . chr($key[0]) . chr($key[1]) . chr($key[2]) . ": ";
            echo $message;
            echo "\n";
            echo "Total = " . $total;
            echo "\n";
        }
    }
}

echo "Time: " . (microtime(true) - $start) . "\n";
