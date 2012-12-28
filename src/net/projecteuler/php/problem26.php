<?php

$answerArr = array();
$answerArr[0] = 0;
$answerArr[1] = 0;

$maxCycle = "";

$patternArr = array();
for($i = 2; $i < 1000; ++$i) {
    $cycle = "";
    $min = 1000;
    $num = bcdiv("1", "$i", 1000);
    $num = substr_replace($num, "", 0, 2);
    array_push($answerArr, $num);

    $numArr = str_split($num);

    $runningString = "";
    $prevRunningString = "";
    $ignoreLeadingZeroes = true;
    $prevStringLeft = "";
    for($j = 0; $j < floor(0.5 * count($numArr)); ++$j) {
        if($ignoreLeadingZeroes && $numArr[$j] == 0)
            continue;

        if($numArr[$j] > 0)
            $ignoreLeadingZeroes = false;

        $pattern = "/00000*/";
        if(preg_match_all($pattern, $num, $matches))
            break;
        $pattern = "/11111*/";
        if(preg_match_all($pattern, $num, $matches))
            break;
        $pattern = "/22222*/";
        if(preg_match_all($pattern, $num, $matches))
            break;
        $pattern = "/33333*/";
        if(preg_match_all($pattern, $num, $matches))
            break;
        $pattern = "/44444*/";
        if(preg_match_all($pattern, $num, $matches))
            break;
        $pattern = "/55555*/";
        if(preg_match_all($pattern, $num, $matches))
            break;
        $pattern = "/66666*/";
        if(preg_match_all($pattern, $num, $matches))
            break;
        $pattern = "/77777*/";
        if(preg_match_all($pattern, $num, $matches))
            break;
        $pattern = "/88888*/";
        if(preg_match_all($pattern, $num, $matches))
            break;
        $pattern = "/99999*/";
        if(preg_match_all($pattern, $num, $matches))
            break;

        $runningString .= $numArr[$j];

        $split = substr($runningString, 0, (floor(strlen($runningString) / 2)));

        $pattern = "/$runningString/";

        $stringLeft = preg_replace($pattern, "", $num);

        // Keep going
        // If the number of characters becomes greater, then we've surpassed our cycle.
        if($j > 5 && strlen($stringLeft) > strlen($prevStringLeft)) {
            echo "went past the CYCLE: " . $prevStringLeft . "\n";
            break;
        }

        $prevStringLeft = $stringLeft;
        $min = strlen($stringLeft);
        $cycle = $runningString;
        $patternArr[$i] = $cycle;

        if(strlen($cycle) > strlen($maxCycle)) {
            $maxCycle = $cycle;
        }
    }


/**
10040160642570281124497991967871485943775100401606425702811244979919678714859437751004016064257028112449799196787148594377510040160642570281124497991967871485943775100401606425702811244979919678714859437751004016064257028112449799196787148594377510040160642570281124497991967871485943775100401606425702811244979919678714859437751004016064257028112449799196787148594377510040160642570281124497991967871485943775100401606425702811244979919678714859437751004016064257028112449799196787148594377510040160642570281124497991967871485943775100401606425702811244979919678714859437751004016064257028112449799196787148594377510040160642570281124497991967871485943775100401606425702811244979919678714859437751004016064257028112449799196787148594377510040160642570281124497991967871485943775100401606425702811244979919678714859437751004016064257028112449799196787148594377510040160642570281124497991967871485943775100401606425702811244979919678714859437751004016064257028112449799196787148594377510040160642570] => 10040160642570281124497991967871485943775
 */
}

$patternArr = sort($patternArr);
print_r($patternArr);

echo "maxCycle = " . $cycle . "\n";
?>
