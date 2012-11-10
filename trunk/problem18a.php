<?php

require_once 'Opus11/DigraphAsMatrix.php';
require_once 'Opus11/Box.php';
require_once 'Opus11/Algorithms.php';


$file = fopen("/home/bdetweiler/src/projecteuler/triangle3.txt", "r") ;  


$triangleNumArr[] = 0;
$runningTotal = 0;
// Figure out how big our graph is using triangle numbers
// Level of the tringle we are trying to solve
$triangleNum = 0;
while(!feof($file))
{

    $currentLine = fgets($file) ;

    if(trim($currentLine) == "")
        break;

    ++$triangleNum;
    $runningTotal += $triangleNum;
    array_push($triangleNumArr, $runningTotal);
}   

fclose($file) ;

// Reverse-encode the numbers in reverse order so we can use Dijkstra's
$codeArr[] = 0;
$j = 99;
for($i = 1; $i < 100; ++$i) {
    $codeArr[$i] = $j;
    --$j;
}

$totalNodesInMatrix = $triangleNumArr[$triangleNum] + 2;

$graph = new DigraphAsMatrix($totalNodesInMatrix); // $triangleNumArr[$triangleNum]);

// Add all vertices to the graph up front
for($i = 0; $i <= $triangleNumArr[$triangleNum] + 1; ++$i)
    $graph->addVertex($i);


$file = fopen("/home/bdetweiler/src/projecteuler/triangle3.txt", "r") ;  

// Populate Graph
$nodeNum = 0;
$triangleNumLevel = 1;
$firstFlag = true;

while(!feof($file))
{
    $currentLine = fgets($file) ;

    if(trim($currentLine) == "")
        break;

    echo "triangNumLevel = " . $triangleNumLevel . "\n";



    $numArr = explode(" ", $currentLine);

    for($i = 0; $i < count($numArr); ++$i) {

        // Turn these into integers (remove leading 0's)
        $numArr[$i] = ($numArr[$i] * 1);

        ++$nodeNum;

        echo " nodeNum = " . $nodeNum . ": " . $numArr[$i] . "\n";

        // Add our lead in node (0 -> 1)
        if($firstFlag) {
            echo "Adding Edge (first): " . 0 . ", " . 1 . ", " . 1 . "\n";
            
            // ($nodeNum - $triangleNumLevel - 1)
            $graph->addEdge(0, 1, boxedInt($codeArr[$numArr[$i]]));
            $firstFlag = true;

            echo "Graph now! " . str($graph) . "\n";

            $firstFlag = false;

            continue;
        }

        // Do something special here
        if($i == 0) {

            echo "FIRST NODE IN ROW $triangleNumLevel\n";
            echo "Adding Edge: " . ($nodeNum - $triangleNumLevel + 1) . ", " . $nodeNum . ", " . $codeArr[$numArr[$i]] . "\n";
            $graph->addEdge(($nodeNum - $triangleNumLevel + 1), $nodeNum, boxedInt($codeArr[$numArr[$i]]));

        // Do something special here 
        } else if($i == (count($numArr) - 1)) {
            
            echo "LAST NODE IN ROW $triangleNumLevel\n";

            echo "Adding Edge: " . (($nodeNum - $triangleNumLevel) + 1) . ", " . $nodeNum . ", " . $codeArr[$numArr[$i]] . "\n";
            $graph->addEdge(($nodeNum - $triangleNumLevel), $nodeNum, boxedInt($codeArr[$numArr[$i]]));

        // This is a middle node
        } else {

            echo "MIDDLE NODE IN ROW $triangleNumLevel\n";
            echo "Adding Edge: " . ($nodeNum - $triangleNumLevel) . ", " . $nodeNum . ", " . $codeArr[$numArr[$i]] . "\n";
            $graph->addEdge(($nodeNum - $triangleNumLevel), $nodeNum, boxedInt($codeArr[$numArr[$i]]));

            echo "Adding Edge: " . (($nodeNum - $triangleNumLevel) + 1) . ", " . $nodeNum . ", " . $codeArr[$numArr[$i]] . "\n";
            $graph->addEdge(($nodeNum - $triangleNumLevel + 1), $nodeNum, boxedInt($codeArr[$numArr[$i]]));
        }


        echo "Graph now! " . str($graph);



        // if($triangleNumArr[$triangleNum + 1] < $nodeNum)
            // $graph->addEdge(($nodeNum - $triangleNumLevel) , 1, boxedInt($codeArr[1]));


        // TODO: figure out last flag
    }


    ++$triangleNumLevel;
}

fclose($file) ;


$nodeNum -= count($numArr);
// Point the last row to a dummy sink
for($i = 0; $i < count($numArr); ++$i) {
    ++$nodeNum;
    echo "Adding Edge: " . $nodeNum . ", " . $nodeNum . ", " . $codeArr[1] . "\n";
    $graph->addEdge($nodeNum, ($totalNodesInMatrix - 1), boxedInt($codeArr[1]));
}


        echo "Graph now! " . str($graph);


$algorithms = new Algorithms();

echo "edges: " . $graph->getNumberOfEdges() . "\n";
echo "vertices: " . $graph->getNumberOfEdges() . "\n";

$answerGraph = Algorithms::dijkstrasAlgorithm($graph, 1);

$vNext = $answerGraph->getVertex($totalNodesInMatrix - 1);


$vNext = $vNext->getSuccessors()->getIterator()->current();

$answerArr = array();
do {
    echo " iterator: " . $vNext->getNumber() . ": " . str($vNext->getWeight()) . "\n";
    array_push($answerArr, $vNext->getNumber());
    $vNext = $vNext->getSuccessors()->getIterator()->current();
} while($vNext->getNumber() != 1);

array_push($answerArr, $vNext->getNumber());

// Currently, the array is backwards. Reverse it.
$answerArr = array_reverse($answerArr);

$weight = $graph->getEdge(0, 1)->getWeight()->getValue();
$total  = $codeArr[$weight];

for($i = 0; $i < count($answerArr) - 1; ++$i) {
    echo "getting NODE: $answerArr[$i]: " . str($graph->getEdge($answerArr[$i], $answerArr[$i + 1])) . "\n";
    $weight = $graph->getEdge($answerArr[$i], $answerArr[$i + 1])->getWeight()->getValue();

    $total += $codeArr[$weight]; // $graph->getVertex($answerArr[$i])->getWeight()->getValue();
}

echo "total = $total\n";

function boxedInt($i) {
    return new BoxedInteger($i);
}

?>
