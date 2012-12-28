<?php
/**
 * File: problem18.php
 * Author: Brian Detweiler
 */

require_once 'Structures/Graph.php';

$directedGraph =& new Structures_Graph(true);




$nodeOne   =& new Structures_Graph_Node();
$nodeTwo   =& new Structures_Graph_Node();
$nodeThree =& new Structures_Graph_Node();
$nodeFour  =& new Structures_Graph_Node();
$nodeFive  =& new Structures_Graph_Node();
$nodeSix   =& new Structures_Graph_Node();
$nodeSeven =& new Structures_Graph_Node();
$nodeEight =& new Structures_Graph_Node();
$nodeNine  =& new Structures_Graph_Node();
$nodeTen   =& new Structures_Graph_Node();

$nodeOne->setMetadata("name",   "1");
$nodeTwo->setMetadata("name",   "2");
$nodeThree->setMetadata("name", "3");
$nodeFour->setMetadata("name",  "4");
$nodeFive->setMetadata("name",  "5");
$nodeSix->setMetadata("name",   "6");
$nodeSeven->setMetadata("name", "7");
$nodeEight->setMetadata("name", "8");
$nodeNine->setMetadata("name",  "9");
$nodeTen->setMetadata("name",   "10");

$nodeOne->setData(3);
$nodeTwo->setData(7);
$nodeThree->setData(4);
$nodeOne->setData(2);
$nodeTwo->setData(4);
$nodeThree->setData(6);
$nodeOne->setData(8);
$nodeTwo->setData(5);
$nodeThree->setData(9);
$nodeOne->setData(3);

$directedGraph->addNode(&$nodeOne);
$directedGraph->addNode(&$nodeTwo);
$directedGraph->addNode(&$nodeThree);
$directedGraph->addNode(&$nodeFour);
$directedGraph->addNode(&$nodeFive);
$directedGraph->addNode(&$nodeSix);
$directedGraph->addNode(&$nodeSeven);
$directedGraph->addNode(&$nodeEight);
$directedGraph->addNode(&$nodeNine);
$directedGraph->addNode(&$nodeTen);

$nodes = array(&$nodeOne,
               &$nodeTwo,
               &$nodeThree,
               &$nodeFour,
               &$nodeFive,
               &$nodeSix,
               &$nodeSeven,
               &$nodeEight,
               &$nodeNine,
               &$nodeTen);


$nodeOne->connectTo($nodeTwo);
$nodeOne->connectTo($nodeThree);

$nodeTwo->connectTo($nodeFour);
$nodeTwo->connectTo($nodeFive);

$nodeThree->connectTo($nodeFive);
$nodeThree->connectTo($nodeSix);

$nodeFour->connectTo($nodeSeven);
$nodeFour->connectTo($nodeEight);

$nodeFive->connectTo($nodeEight);
$nodeFive->connectTo($nodeNine);

$nodeSix->connectTo($nodeNine);
$nodeSix->connectTo($nodeTen);

print("NodeTwo's Data is an integer: " . $nodeTwo->getData() . "\n");
print("NodeThree's Data is an integer: " . $nodeThree->getData() . "\n");

reverseDijkstra($nodes, $nodeOne, 10);


function reverseDijkstra($graph, $source, $size) {

    /*
    print("NodeOne's inDegree: " . $nodeOne->inDegree());
print("NodeOne's outDegree: " . $nodeOne->outDegree());

// and naturally, nodes can report on their arcs
$arcs = $nodeOne->getNeighbours();
for ($i=0;$i<sizeof($arcs);$i++) {
    print("NodeOne has an arc to " . $arcs[$i]->getData());
}
*/

    $Q = $graph;


    $dist = array();
    $prev = array();
    for($i = 0; $i < $size; ++$i) {
        $dist[$graph[$i]->getMetadata("name")] = -1;
        $prev[$graph[$i]->getMetadata("name")] = "";
    }

    $dist[$source->getMetadata("name")] = 0;

    while(count($Q) > 0) {
        arsort($dist);

        // Vertex in Q with the largest distance in dist[]
        $u = $Q[$dist[0]];

        if($dist[0] == -1)
            break;

        unset($Q[$u]);

        $neighbors = $u->getNeighbours();
        for($i = 0; $i < count($neighbors); ++$i) {
            $alt = $dist[$u] + $neighbors[$i]->getData();

            if($alt > $dist[$neighbors[$i]]) {
                $dist[$neighbors[$i]] = $alt;
                $prev[$neighbors[$i]] = $u;
            }
        }
    }

print_r($dist);

}
/*
11      while Q is not empty:                                      // The main loop
12          u := vertex in Q with smallest distance in dist[] ;    // Start node in first case
13          if dist[u] = infinity:
14              break ;                                            // all remaining vertices are
15                                                                 // inaccessible from source
16          end if ;
17          remove u from Q ;
18          for each neighbor v of u:                              // where v has not yet been 
19                                                                                 removed from Q.
20              alt := dist[u] + dist_between(u, v) ;
21              if alt < dist[v]:                                  // Relax (u,v,a)
22                  dist[v] := alt ;
23                  previous[v] := u ;
24                  decrease-key v in Q;                           // Reorder v in the Queue
25              end if ;
26          end for ;
27      end while ;
28      return dist[] ;
29  end Dijkstra.
*/



?>
