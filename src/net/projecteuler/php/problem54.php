<?php

/**
 * File:    problem54.php
 * Author:  Brian Detweiler
 */

define("T", 11);
define("J", 11);
define("Q", 12);
define("K", 13);
define("A", 14);

define("HIGH_CARD", pow(2, 4));
define("ONE_PAIR", pow(2, 5));
define("TWO_PAIRS", pow(2, 6));
define("THREE_OF_A_KIND", pow(2, 7));
define("STRAIGHT", pow(2, 8));
define("FLUSH", pow(2, 9));
define("FULL_HOUSE", pow(2, 10));
define("FOUR_OF_A_KIND", pow(2, 11));
define("STRAIGHT_FLUSH", pow(2, 12));
define("ROYAL_FLUSH", pow(2, 13));

$handValues = array();

$val = 1;
// Suit will go in the order: Hearts, Diamonds, Clubs, Spades
for($i = 2; $i < 10; ++$i) {
    ++$val;
    $handValues[$i . "H"] = $val;
    $handValues[$i . "D"] = $val;
    $handValues[$i . "C"] = $val;
    $handValues[$i . "S"] = $val;
}

++$val;
$handValues["TH"] = $val;
$handValues["TD"] = $val;
$handValues["TC"] = $val;
$handValues["TS"] = $val;
++$val;
$handValues["JH"] = $val;
$handValues["JD"] = $val;
$handValues["JC"] = $val;
$handValues["JS"] = $val;
++$val;
$handValues["QH"] = $val;
$handValues["QD"] = $val;
$handValues["QC"] = $val;
$handValues["QS"] = $val;
++$val;
$handValues["KH"] = $val;
$handValues["KD"] = $val;
$handValues["KC"] = $val;
$handValues["KS"] = $val;
++$val;
$handValues["AH"] = $val;
$handValues["AD"] = $val;
$handValues["AC"] = $val;
$handValues["AS"] = $val;

$numberList = array();

$start = microtime(true);

$handle = @fopen("/home/bdetweiler/src/projecteuler/poker.txt", "r");

$gameNumber = 0;
$player1 = 0;
$player2 = 0;
while(($buffer = fgets($handle, 30)) !== false) {
    $cards = explode(" ", trim($buffer));

    if(count($cards) == 1)
        continue;

    ++$gameNumber;

    $hand1 = array();
    $hand2 = array();

    // Deal
    array_push($hand1, $cards[0]);
    array_push($hand1, $cards[1]);
    array_push($hand1, $cards[2]);
    array_push($hand1, $cards[3]);
    array_push($hand1, $cards[4]);

    array_push($hand2, $cards[5]);
    array_push($hand2, $cards[6]);
    array_push($hand2, $cards[7]);
    array_push($hand2, $cards[8]);
    array_push($hand2, $cards[9]);

    $hand1 = orderHand($hand1);
    $hand2 = orderHand($hand2);
    $handValue1 = determineHandValue($hand1);
    $handValue2 = determineHandValue($hand2);

    // Tie breaker
    if($handValue1 == $handValue2) {
        $handValue1 += $handValues[getHighCard($hand1)];
        $handValue2 += $handValues[getHighCard($hand2)];
        if($handValue1 == $handValue2) {
            $handValue1 += $handValues[getHighCard(array_slice($hand1, 0, 4))];
            $handValue2 += $handValues[getHighCard(array_slice($hand2, 0, 4))];
            if($handValue1 == $handValue2) {
                $handValue1 += $handValues[getHighCard(array_slice($hand1, 0, 3))];
                $handValue2 += $handValues[getHighCard(array_slice($hand2, 0, 3))];
                if($handValue1 == $handValue2) {
                    $handValue1 += $handValues[getHighCard(array_slice($hand1, 0, 2))];
                    $handValue2 += $handValues[getHighCard(array_slice($hand2, 0, 2))];
                    if($handValue1 == $handValue2) {
                        $handValue1 += $handValues[getHighCard(array_slice($hand1, 0, 1))];
                        $handValue2 += $handValues[getHighCard(array_slice($hand2, 0, 1))];
                    }
                }
            }
        }
    }


    // echo "========================== GAME $gameNumber ==========================\n";

    if($handValue1 > $handValue2) {
        ++$player1;
        // echo "PLAYER 1 IS THE WINNER with " . determineHand($hand1) . " [$handValue1] points\n";
        // print_r($hand1);
        // echo "PLAYER 2 is the loser  with " . determineHand($hand2) . " [$handValue2] points\n";
        // print_r($hand2);
    } else {
        ++$player2;
        // echo "PLAYER 1 is the loser  with " . determineHand($hand1) . " [$handValue1] points\n";
        // print_r($hand1);
        // echo "PLAYER 2 IS THE WINNER with " . determineHand($hand2) . " [$handValue2] points\n";
        // print_r($hand2);
    }
}

fclose($handle);

echo "Player1 won $player1 games out of $gameNumber games\n";
echo "Player2 won $player2 games out of $gameNumber games\n";
echo "Time: " . (microtime(true) - $start) . "\n";


function orderHand($hand) {

    global $handValues;

    $card0 = $hand[0];
    $card1 = $hand[1];
    $card2 = $hand[2];
    $card3 = $hand[3];
    $card4 = $hand[4];

    $value0 = $handValues[$card0];
    $value1 = $handValues[$card1];
    $value2 = $handValues[$card2];
    $value3 = $handValues[$card3];
    $value4 = $handValues[$card4];

    $valuesArr = array();
    array_push($valuesArr, $value0);
    array_push($valuesArr, $value1);
    array_push($valuesArr, $value2);
    array_push($valuesArr, $value3);
    array_push($valuesArr, $value4);
    sort($valuesArr);

    $orderedHand = array();

    $cardZeroLeft  = true;
    $cardOneLeft   = true;
    $cardTwoLeft   = true;
    $cardThreeLeft = true;
    $cardFourLeft  = true;
    for($i = 0; $i < count($valuesArr); ++$i) {

        if($cardZeroLeft && $handValues[$card0] == $valuesArr[$i]) {
            array_push($orderedHand, $card0);
            $cardZeroLeft = false;
        } else if($cardOneLeft && $handValues[$card1] == $valuesArr[$i]) {
            array_push($orderedHand, $card1);
            $cardOneLeft = false;
        } else if($cardTwoLeft && $handValues[$card2] == $valuesArr[$i]) {
            array_push($orderedHand, $card2);
            $cardTwoLeft = false;
        } else if($cardThreeLeft && $handValues[$card3] == $valuesArr[$i]) {
            array_push($orderedHand, $card3);
            $cardThreeLeft = false;
        } else if($cardFourLeft && $handValues[$card4] == $valuesArr[$i]) {
            array_push($orderedHand, $card4);
            $cardFourLeft = false;
        }
    }

    return $orderedHand;

}

function isRoyalFlush($hand) {
    if(!hasFlush($hand) || !hasStraight($hand))
        return false;

    $card0 = str_split($hand[0]);
    $card1 = str_split($hand[1]);
    $card2 = str_split($hand[2]);
    $card3 = str_split($hand[3]);
    $card4 = str_split($hand[4]);

    if($card0[0] == "T" && 
       $card1[0] == "J" &&
       $card2[0] == "Q" &&
       $card3[0] == "K" &&
       $card4[0] == "A")
        return true;

    return false;

}

function hasFlush($hand) {

    $card0 = str_split($hand[0]);
    $card1 = str_split($hand[1]);
    $card2 = str_split($hand[2]);
    $card3 = str_split($hand[3]);
    $card4 = str_split($hand[4]);

    $cardString = "";
    $cardString .= $card0[1];
    $cardString .= $card1[1];
    $cardString .= $card2[1];
    $cardString .= $card3[1];
    $cardString .= $card4[1];

    if($cardString == "HHHHH" ||
       $cardString == "DDDDD" ||
       $cardString == "CCCCC" ||
       $cardString == "SSSSS")
        return true;

    return false;
}

function hasStraight($hand) {

    global $handValues;

    if(($handValues[$hand[0]] + 1) == $handValues[$hand[1]] &&
       ($handValues[$hand[1]] + 1) == $handValues[$hand[2]] &&
       ($handValues[$hand[2]] + 1) == $handValues[$hand[3]] &&
       ($handValues[$hand[3]] + 1) == $handValues[$hand[4]])
        return true;

    return false;
}

function isStraight($hand) {
    return !hasFlush($hand) && hasStraight($hand);
}

function isFlush($hand) {
    return hasFlush($hand) && !hasStraight($hand);
}

function isStraightFlush($hand) {
    return hasStraight($hand) && hasFlush($hand) && !isRoyalFlush($hand);
}

function hasPair($hand) {

    global $handValues;

    if($handValues[$hand[0]] == $handValues[$hand[1]] ||
       $handValues[$hand[1]] == $handValues[$hand[2]] ||
       $handValues[$hand[2]] == $handValues[$hand[3]] ||
       $handValues[$hand[3]] == $handValues[$hand[4]])
        return true;
}

function hasThreeOfAKind($hand) {

    global $handValues;

    if(!hasPair($hand))
        return false;

    if($handValues[$hand[0]] == $handValues[$hand[1]])
        if($handValues[$hand[1]] == $handValues[$hand[2]])
            return true;

    if($handValues[$hand[1]] == $handValues[$hand[2]])
        if($handValues[$hand[2]] == $handValues[$hand[3]])
            return true;

    if($handValues[$hand[2]] == $handValues[$hand[3]])
        if($handValues[$hand[3]] == $handValues[$hand[4]])
            return true;

    return false;
}

function hasFourOfAKind($hand) {
    global $handValues;

    if(!hasThreeOfAKind($hand))
        return false;

    if($handValues[$hand[0]] == $handValues[$hand[1]])
        if($handValues[$hand[1]] == $handValues[$hand[2]])
            if($handValues[$hand[2]] == $handValues[$hand[3]])
                return true;

    if($handValues[$hand[1]] == $handValues[$hand[2]])
        if($handValues[$hand[2]] == $handValues[$hand[3]])
            if($handValues[$hand[3]] == $handValues[$hand[4]]) return true; return false;
}

function isFourOfAKind($hand) {
    return hasFourOfAKind($hand);
}

function isThreeOfAKind($hand) {
    return (hasThreeOfAKind($hand) && !hasFourOfAKind($hand) && !isFullHouse($hand));
}

function isFullHouse($hand) {
    global $handValues;
    if(!hasThreeOfAKind)
        return false;

    if($handValues[$hand[0]] == $handValues[$hand[1]] && 
       $handValues[$hand[1]] == $handValues[$hand[2]] &&
       $handValues[$hand[2]] != $handValues[$hand[3]])
        return ($handValues[$hand[3]] == $handValues[$hand[4]]);

    if($handValues[$hand[2]] == $handValues[$hand[3]] && 
       $handValues[$hand[3]] == $handValues[$hand[4]] &&
       $handValues[$hand[1]] != $handValues[$hand[2]])
        return ($handValues[$hand[0]] == $handValues[$hand[1]]);

    return false;
}

function isOnePair($hand) {

    if(isTwoPairs($hand))
        return false;

    return (hasPair($hand) && !hasThreeOfAKind($hand));
}

function isTwoPairs($hand) {

    global $handValues;

    if(!hasPair($hand))
        return false;

    if(hasFourOfAKind($hand) || hasThreeOfAKind($hand))
        return false;

    if($handValues[$hand[0]] == $handValues[$hand[1]])
        if($handValues[$hand[2]] == $handValues[$hand[3]])
            return true;

    if($handValues[$hand[0]] == $handValues[$hand[1]])
        if($handValues[$hand[3]] == $handValues[$hand[4]])
            return true;

    if($handValues[$hand[1]] == $handValues[$hand[2]])
        if($handValues[$hand[3]] == $handValues[$hand[4]])
            return true;
}

function getHighCard($hand) {

    global $handValues;
    $max = "2H";
    for($i = 0; $i < count($hand); ++$i)
        if($handValues[$hand[$i]] > $handValues[$max])
            $max = $hand[$i];

    return $max;
}

function getHighCardOfRoyalFlush($hand) {

    if(!isRoyalFlush($hand))
        return null;

    return getHighCard($hand);
}

function getHighCardOfFourOfAKind($hand) {

    global $handValues;
    if(!isFourOfAKind($hand))
        return null;

    if($handValues[$card0] == $handValues[$card1])
        return $hand[0];
    else
        return $hand[1];
}

// Full house high card is based on the three hand
function getHighCardOfFullHouse($hand) {

    if(!isFullHouse($hand))
        return null;

    if($handValues[$hand[0]] == $handValues[$hand[1]] &&
       $handValues[$hand[1]] == $handValues[$hand[2]])
        return getHighCard(array_slice($hand, 0, 3));

    return getHighCard(array_slice($hand, 2));
}

function getHighCardOfFlush($hand) {

    if(!isFlush($hand))
        return null;
    
    return getHighCard($hand);
}

function getHighCardOfStraight($hand) {

    if(!isStraight($hand))
        return null;

    return getHighCard($hand);
}

function getHighCardOfStraightFlush($hand) {

    if(!isStraightFlush($hand))
        return null;

    return getHighCard($hand);
}

function getHighCardOfThreeOfAKind($hand) {

    global $handValues;
    if(!isThreeOfAKind($hand))
        return null;

    if($handValues[$hand[0]] == $handValues[$hand[1]])
        return $hand[0];
    else if($handValues[$hand[1]] == $handValues[$hand[2]])
        return $hand[1];
    else 
        return $hand[2];
}

function getHighCardOfTwoPairs($hand) {

    global $handValues;
    if(!isTwoPairs($hand))
        return null;

    if($handValues[$hand[4]] == $handValues[$hand[3]])
        return $hand[3];

    return $hand[2];
}

function getHighCardOfOnePair($hand) {

    global $handValues;

    if(!isOnePair($hand))
        return null;

    if($handValues[$hand[0]] == $handValues[$hand[1]] || $handValues[$hand[1]] == $handValues[$hand[2]])
        return $hand[1];
    
    return $hand[3];
}

function determineHandValue($hand) {

    global $handValues;

    if(isRoyalFlush($hand))
        return ROYAL_FLUSH + $handValues[getHighCardOfRoyalFlush($hand)];

    if(isStraightFlush($hand))
        return STRAIGHT_FLUSH + $handValues[getHighCardOfStraightFlush($hand)];

    if(isFourOfAKind($hand))
        return FOUR_OF_A_KIND + $handValues[getHighCardOfFourOfAKind($hand)];

    if(isFullHouse($hand))
        return FULL_HOUSE + $handValues[getHighCardOfFullHouse($hand)];

    if(isFlush($hand))
        return FLUSH + $handValues[getHighCardOfFlush($hand)];

    if(isStraight($hand))
        return STRAIGHT + $handValues[getHighCardOfStraight($hand)];

    if(isThreeOfAKind($hand))
        return THREE_OF_A_KIND + $handValues[getHighCardOfThreeOfAKind($hand)];

    if(isTwoPairs($hand))
        return TWO_PAIRS + $handValues[getHighCardOfTwoPairs($hand)];

    if(isOnePair($hand))
        return ONE_PAIR + $handValues[getHighCardOfOnePair($hand)];

    return $handValues[getHighCard($hand)];
}

function determineHand($hand) {

    global $handValues;

    if(isRoyalFlush($hand))
        return "Royal Flush";

    if(isStraightFlush($hand))
        return "Straight Flush";

    if(isFourOfAKind($hand))
        return "Four of a Kind";

    if(isFullHouse($hand))
        return "Full House";

    if(isFlush($hand))
        return "Flush";

    if(isStraight($hand))
        return "Straight";

    if(isThreeOfAKind($hand))
        return "Three of a Kind";

    if(isTwoPairs($hand))
        return "Two Pairs";

    if(isOnePair($hand))
        return "One Pair";

    return "High Card: " . getHighCard($hand);
}

?>
