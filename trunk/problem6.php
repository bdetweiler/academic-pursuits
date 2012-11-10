<?php

    $sumOfSquares = 0;
    for($i = 1; $i <= 100; ++$i) {
        echo $i . " ^ 2 = " . pow($i,  2) . "\n";
        $sumOfSquares += pow($i,  2);
    }

    echo "Sum of Squares: " . $sumOfSquares . "\n";

    $squareOfSums = 0;
    for($j = 1; $j <= 100; ++$j) {
        $squareOfSums += $j;
    }

    $squareOfSums = pow($squareOfSums, 2);

    echo "Square of Sums: " . $squareOfSums . "\n";

    echo "diff: " . abs($sumOfSquares - $squareOfSums) . "\n";


?>
