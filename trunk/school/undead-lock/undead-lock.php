<?php
 /**
 * @copyright Copyright (c) 2009 by Brian R. Detweiler
 *
 * @author $Author: bdetweiler $
 * @version $Id: NECTJGrammar.php, Exp $
 * @package undead-lock
 */

/**
 * @package undead-lock
 */

require_once('Scanner.php');
require_once('Simulation.php');

$scanner = new Scanner();
$debug = false;

// If we are trying to execute this class directly
if(realpath($argv[0]) == realpath(__FILE__))
{
    // No CLI argument
    if($argc < 2)
    {
        echo "Please specify a file\n";
        exit(1);
    }

    if($argc > 2)
        $debug = true;
}

$filename = $argv[1];
$status = 0;
if(is_file($filename) && is_readable($filename))
    $file = fopen($filename, 'r');
else
    $status = 1;

$scanner = new Scanner($filename);
$tokenizedSimulation = $scanner->scan($filename);

$i = 1;
foreach($tokenizedSimulation as $sim)
{

    if($sim[0][0] == 0 &&
       $sim[0][1] == 0)
        break;
    print("Simulation $i\n"); 
    $simulation = new Simulation($sim, $debug);
    $simulation->simulate();
    
    ++$i;
}

return $status;


?>
