<?php

$boogers = "";
for($i = 1; $i <= 1000; ++$i) {

    $tmp = $i;

    if($tmp >= 1000) {
        $boogers .= "onethousand";
        $tmp -= 1000;

    }

    if($tmp >= 100) {

        $boogers .= getSingle(floor($tmp / 100)) . "hundred";
      
        // Remove the hundreds
        $tmp -= (floor($tmp / 100) * 100);

        if($tmp > 0)
            $boogers .= "and";

    }

    if($tmp < 10) {
        $boogers .= getSingle($tmp);
    } else if($tmp >= 10 && $tmp <= 20) {
        $boogers .= getDouble($tmp);
    } else {
        $boogers .= getDouble(floor($tmp / 10) * 10);
        $tmp -= floor($tmp / 10) * 10;
        $boogers .= getSingle($tmp);
    }
}

echo "Boogers : " . count(str_split($boogers)) . "\n";

function getSingle($single) {

    $boners = "";

    switch($single) {
        case 1:
            $boners .= "one";
            break;
        case 2:
            $boners .= "two";
            break;
        case 3:
            $boners .= "three";
            break;
        case 4:
            $boners .= "four";
            break;
        case 5:
            $boners .= "five";
            break;
        case 6:
            $boners .= "six";
            break;
        case 7:
            $boners .= "seven";
            break;
        case 8:
            $boners .= "eight";
            break;
        case 9:
            $boners .= "nine";
            break;
        default:
            $boners .= "";
        
    }

    return $boners;
}

function getDouble($double) {

    $peepee = "";

    switch($double) {
        case 10:
            $peepee .= "ten";
            break;
        case 11:
            $peepee .= "eleven";
            break;
        case 12:
            $peepee .= "twelve";
            break;
        case 13:
            $peepee .= "thirteen";
            break;
        case 14:
            $peepee .= "fourteen";
            break;
        case 15:
            $peepee .= "fifteen";
            break;
        case 16:
            $peepee .= "sixteen";
            break;
        case 17:
            $peepee .= "seventeen";
            break;
        case 18:
            $peepee .= "eighteen";
            break;
        case 19:
            $peepee .= "nineteen";
            break;
        case 20:
            $peepee .= "twenty";
            break;
        case 30:
            $peepee .= "thirty";
            break;
        case 40:
            $peepee .= "forty";
            break;
        case 50:
            $peepee .= "fifty";
            break;
        case 60:
            $peepee .= "sixty";
            break;
        case 70:
            $peepee .= "seventy";
            break;
        case 80:
            $peepee .= "eighty";
            break;
        case 90:
            $peepee .= "ninety";
            break;
        default:
            $peepee = "";
            break;
        
    }

    return $peepee;
}

?>
