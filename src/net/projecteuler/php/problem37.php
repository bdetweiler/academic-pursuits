<?php

$file = fopen("/home/bdetweiler/src/projecteuler/primes1.txt", "r") ;  


$sum = 0;
$count = 0;
$primeArr = array();
while(!feof($file))
{
    $primeCandidate = trim(fgets($file));

    if($primeCandidate == "")
        continue;


    $primeArr[$primeCandidate] = true;

    if($primeCandidate < 11)
        continue;

    $primeCandidateLeft = $primeCandidate;
    $primeCandidateRight = $primeCandidate;


    $isTruncatable = true;
    while(strlen($primeCandidateLeft) > 1) {
        $primeCandidateLeft = substr($primeCandidateLeft, 1); 
        if(!$primeArr[$primeCandidateLeft]) {
            $isTruncatable = false;
            break;
        }
    }

    // If the first one didn't work, let's move on
    if(!$isTruncatable)
        continue;

    while(strlen($primeCandidateRight) > 1) {
        $primeCandidateRight = substr($primeCandidateRight, 0, -1);
        if(!$primeArr[$primeCandidateRight]) {
            $isTruncatable = false;
            break;
        }
    }

    if(!$isTruncatable)
        continue;

    $sum += $primeCandidate;
    ++$count;
    echo "Truncatable prime: $primeCandidate\n";
    if($count == 11)
        break;

}   
echo "truncatable prime sum: $sum\n";

fclose($file) ;

?>
