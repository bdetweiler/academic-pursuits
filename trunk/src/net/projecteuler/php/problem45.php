<?php
/**
 * File:    problem45.php
 * Author:  Brian Detweiler
 */
include_once('EulerUtils.php');
$EulerUtils = new EulerUtils();

$limit = 100000;
$sum = 0;


$timeStart = microtime(true);

for($i = 286; $i < $limit; ++$i) {
    $tri = $EulerUtils->getTriangleNumber($i);

    // Just to verify
    // $triCandidate = $EulerUtils->isTriangleNumber($tri);
    $pentCandidate = $EulerUtils->isPentagonalNumber($tri);
    $hexCandidate = $EulerUtils->isHexagonalNumber($tri);

    $pent = $EulerUtils->getPentagonalNumber($pentCandidate);
    $hex = $EulerUtils->getHexagonalNumber($hexCandidate);

    if($pentCandidate > 0 && $hexCandidate > 0) {
        // echo "Found two candidates...\n";
        // echo "The $pentCandidate" . "th pent number which is $pent\n";
        // echo "The $hexCandidate" . "th hex number which is $hex\n";

        if($pent == $hex && $hex == $tri) {
            echo "The $i" . "th Triangle Number $tri number is our winner\n";
            echo "The $pentCandidate" . "th Pentagonal number = $pent\n";
            echo "The $hexCandidate" . "th Hexagonal number = $hex\n";
            break;
        }
    }
}

$timeEnd = microtime(true);
echo "sum = $sum\n";
echo ($timeEnd - $timeStart) . "\n";



?>
