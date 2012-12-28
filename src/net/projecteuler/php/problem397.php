<?php
/**
 * File:    problem397.php
 * Author:  Brian Detweiler
 */

$total = f(1, 10);
if($total == 41)
    echo "WORKED! $total\n";
else
    echo "FAIL $total\n";


function f($K, $X) {
    // 1 <= k <= K

    /* Returns the number of integer triplets (k, a, b, c) S.T. at least one angle in ABC is 45 degrees where 
     * 1 <= k <= K 
     * -X <= a < b < c <= X
     */
    $rval = 0;

    $step = 0.1;

    for($k = 1; $k <= $K; ++$k) {
        for($a = -$X; $a < $X; $a += $step) {
            for($b = ($a + $step); $b < $X; $b += $step) {
                for($c = ($b + $step); $c <= $X; $c += $step) {

                    $A = new Point($a, (pow($a, 2) / $k));
                    $B = new Point(-$b, (pow($b, 2) / $k));
                    $C = new Point($c, (pow($c, 2) / $k));

                    $ab = $A->getDistance($B);
                    $bc = $B->getDistance($C);
                    $ca = $C->getDistance($A);

                    if($ab == 0 || $bc == 0 || $ca == 0)
                        continue;

                    $angleA = calculateAngle($ab, $ca, $bc);
                    $angleB = calculateAngle($bc, $ab, $ca);
                    $angleC = calculateAngle($ca, $ab, $bc);


                    if($angleA == 45 || $angleB == 45 || $angleC == 45) {

                        echo "($k, $a, $b, $c)\n";
                        echo "($ab, $bc, $ca) angles: $angleA - $angleB - $angleC\n";
                        ++$rval;
                    }
                        
                }
            }
        }
    }

    return $rval;
}

function calculateAngle($c, $a, $b) {
    $angleInRadians = acos((pow($a, 2) + pow($b, 2) - pow($c, 2)) / (2 * $a * $b));
    return rad2deg($angleInRadians);
}

class Point
{
    public $x;
    public $y;

    function __construct($xArg, $yArg) {
        $this->x = $xArg;
        $this->y = $yArg;
    }

    function getDistance($p) {
        $x1 = $this->x - $p->x;
        $y1 = $this->y - $p->y;
        return sqrt($x1 * $x1 + $y1 * $y1);
    }
}

?>
