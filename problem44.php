<?php
/**
 * File:    problem45.php
 * Author:  Brian Detweiler
 */
include_once('EulerUtils.php');
$EulerUtils = new EulerUtils();

$limit = 500;
$D = 0;
$min = bcadd("10000000000000", "0");


$timeStart = microtime(true);

for($i = 1; $i < $limit; ++$i) {

    $pentK = $EulerUtils->getPentagonalNumber($i);
    
    for($j = $i + 1; $j < $limit; ++$j) {

        $pentJ = $EulerUtils->getPentagonalNumber($j);

        if($EulerUtils->isPentagonalNumber(bcadd($pentJ, $pentK)) > 0) {

            $D = abs(bcsub($pentJ, $pentK));
            if($EulerUtils->isPentagonalNumber($D) > 0){
                if($D < $min) {
                    $min = $D;
                    echo "new min = $min\n";
                    echo "pentJ = $pentJ and pentK = $pentK\n";
                }
            }
            else
                $D = 0;
        }
    }

    // if($D > 0)
        // break;
}


$timeEnd = microtime(true);
echo "min = $min\n";
echo ($timeEnd - $timeStart) . "\n";



?>
