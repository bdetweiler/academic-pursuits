<?php

$n = 10;
echo "n = 10000: " . ((1 / sqrt(5)) * (pow(((1 + sqrt(5)) / 2), $n) - (pow(((1 - sqrt(5)) / 2), $n)))) . "\n";


echo "new: " . ($n / (1 - $n - pow($n, 2))) . "\n";

?>
