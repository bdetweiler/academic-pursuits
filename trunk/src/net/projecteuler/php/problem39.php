<?php
/**
 * File:    problem39.php
 * Author:  Brian Detweiler
 */

include_once("EulerUtils.php");
$EulerUtils = new EulerUtils();

$max = 0;
$limit = 1000;

$sidesArr = array();
$foundArr = array();


$time_start = microtime(true);

for($ab = 1; $ab < $limit; ++$ab) {
    for($bc = 1; $bc < ($limit - $ab); ++$bc) {
        $ca = round($EulerUtils->pythag($ab, $bc));
        if($ca > $limit)
            break;

        $perimeter = ($ab + $bc + $ca) . "";


        if($perimeter > $limit)
            break;

        // echo "$ab, $bc, $ca\n";

        $angleA = $EulerUtils->calculateAngleSSS($ab, $ca, $bc);
        $angleB = $EulerUtils->calculateAngleSSS($bc, $ab, $ca);
        $angleC = $EulerUtils->calculateAngleSSS($ca, $ab, $bc);

        if($angleA == 90 || $angleB == 90 || $angleC == 90) {

            // Only count this configuration of sides once.
            $checkUnique = "";
            
            // SORT
            // A <= B <= C
            if($ab <= $bc && $bc <= $ca)
                $checkUnique = $ab . "_" . $bc . "_" . $ca;
            // A <= C <= B
            else if($ab <= $ca && $ca <= $bc)
                $checkUnique = $ab . "_" . $ca . "_" . $bc;
            // C <= A <= B
            else if($ca <= $ab && $ab <= $bc)
                $checkUnique = $ca . "_" . $ab . "_" . $bc;
            // C <= B <= A
            else if($ca <= $bc && $bc <= $ab)
                $checkUnique = $ca . "_" . $bc . "_" . $ab;
            // B <= A <= C 
            else if($bc <= $ab && $ab <= $ca)
                $checkUnique = $bc . "_" . $ab . "_" . $ca;
            // B <= C <= A
            else if($bc <= $ca && $ca <= $ab)
                $checkUnique = $bc . "_" . $ca . "_" . $ab;
               
            if(!array_key_exists($checkUnique, $sidesArr))
                $sidesArr[$checkUnique] = 1;
            else
                continue;


            if(!array_key_exists($perimeter, $foundArr)) {
                $foundArr[$perimeter] = 1;
            } else {
                $foundArr[$perimeter] += 1;
                if($foundArr[$perimeter] > $max) {
                    $max = $foundArr[$perimeter];
                    echo "New max: $max for $perimeter\n";
                }
            }
        }
    }
}

$time_end = microtime(true);
$time = $time_end - $time_start;

echo "$time\n";

?>
