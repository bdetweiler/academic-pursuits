<?php
/**
 * @copyright Copyright (c) 2009 by Brian R. Detweiler
 *
 * @author $Author: bdetweiler $
 * @version $Id: Simulation.php, Exp $
 * @package undead-lock
 */

require_once('Opus11/DigraphAsMatrix.php');
require_once('Opus11/BoxedInteger.php');
require_once('Opus11/Edge.php');
require_once('Process.php');
//{
/**
 * @package undead-lock
 */

class Simulation
{
    // Number of processes
    protected $np        = 0;
    // Number of resources
    protected $nr        = 0;
    // 2-D Array. The actual process data from the input
    protected $procData  = null;
    // An array that stores Process objects
    // protected $processes = null;
    // The resource allocation graph
    protected $graph     = null;
    // An array. Process-Resource map. Used to map a number to a process/resource name
    protected $prMap     = null;
    // The clock
    protected $time      = 0;

    protected $processes = null;

    protected $waiting   = null;
    protected $ready     = null;


    protected $deadlock  = false;


    protected $debug     = false;

    const REQUEST        = 1;
    const RELEASE        = 2;
    const COMPUTE        = 3;

    // In the data, the INSTRUCTION is the first part of the pair
    const INSTRUCTION    = 0;

    // In the data, the ARGUMENT is the second part of the pair
    // Either a resource to allocate/deallocate or a number of clock cycles to compute for
    const ARGUMENT       = 1;

    /**
     * Constructs a Simulation
     *
     * @note Each simulation begins with two integers.
     *       "0 0" or EOF ends the program.
     *       Here is some sample input:
     *
     *   7 6
     *   7    1 1     3  5   1  2  3  5    2 1     2 2   3 3
     *   4    3 3     1  3   3  5  2  3
     *   5    3 3     1  2   3  2  2  2    3 3
     *   6    1 4     3  6   1  3  2  4    3 2     2 3
     *   6    1 3     3  5   1  5  2  3    2 5     3 2
     *   7    1 6     3  5   1  2  3  2    2 2     2 6   3 3
     *   7    1 5     3  2   1  4  3  5    2 5     3 2   2 4
     *
     *
     */
    public function __construct($simData, $debug = false)
    {

        $this->debug = $debug;

        $this->processes = array();
        $this->ready   = array();
        $this->waiting = array();
        $this->prMap = array();

        // Set the number of processes
        $this->np = $simData[0][0];

        // Set the number of resources
        $this->nr = $simData[0][1];
    
        // Bump the NP/NR part off the array
        array_shift($simData);

        $this->procData = $simData;

        $i = 0;
        foreach($this->procData as $procData)
        {
            array_shift($procData);
            array_push($this->processes, new Process("p" . ++$i, $procData));
        }


        // All processes start in the waiting queue (Using references)
        foreach($this->processes as &$process)
        {
            $process->setWaiting();
            array_push($this->waiting, $process);
        }

        /* This gives us a way to insert integers into the digraph,
         * But still keep the processes separated from the resources
         * Processes and Resources are 1-indexed. (p1, p2, p3, ..., r1, r2, r3, ...)
         */

        // Insert processes
        for($i = 0; $i < $this->np; ++$i)
            $this->prMap[$i] = "p" . ($i + 1);

        // Insert resources
        for($i = $this->np; $i < $this->np + $this->nr; ++$i)
            $this->prMap[$i] = "r" . (abs($i - $this->np) + 1);

        // Start a new graph of size (number of process + number of resources)
        $this->graph = new DigraphAsMatrix($this->np + $this->nr);

        // Insert all the vertices to start with (processes and resources)
        for($i = 0; $i < ($this->np + $this->nr); ++$i)
            $this->graph->addVertex($i, $i);

    }
    
    /**
     * Destructs the Simulation
     *
     */
    public function __destruct()
    {
        $this->np = 0;
        $this->nr = 0;
        $this->procData = null;
        $this->graph = null;
        $this->prMap = null;
        $this->ready = null;
        $this->waiting = null;
        $this->time = 0;
        $this->deadlock = false;
    }
        

    /**
     * Returns a textual representation of a Simulation
     *
     * @return string A string.
     */
    public function __toString()
    {
        print($this->np . " " . $this->nr . "\n");

        for($i = 0; $i < count($this->procData); ++$i)
        {
            for($j = 0; $j < count($this->procData[$i]); ++$j)
            {
                if($j == 0)
                    print("\n" . $this->procData[$i][$j] . "\t");
                else if(($j % 2) == 0)
                    print($this->procData[$i][$j] . "\t");
                else
                    print($this->procData[$i][$j] . " ");
            }
        }

        print("\n");
        print("WAITING QUEUE: ");
        print_r($this->waiting);
        print("READY QUEUE: ");
        print_r($this->ready);

        return "";
    }

    /**
     * Example:
     *   1 1     1 2    3 2   2 1     2 2
     *   1 1     1 2    3 2   2 1     2 2
     *   1 3     3 5    2 3   3 2
     */
    public function simulate()
    {
        // Copy this into local scope because we don't want to modify the actual data itself
        $procData = $this->procData;

        // While there is still a process in the waiting queue 
        while(count($this->waiting) && !$this->deadlock)
        {
            $curProc = array_shift($this->waiting);
            $inst = $curProc->getInstruction();

            if($curProc->getState() != "BLOCKED")
            {
                if($this->debug)
                    print($this->time 
                          . ": process " 
                          . ($curProc->getProcNumber() + 1) 
                          . " (" 
                          . $inst[self::INSTRUCTION] 
                          . "," 
                          . $inst[self::ARGUMENT] 
                          . ")\n");

                switch($inst[self::INSTRUCTION])
                {
                    case self::REQUEST:
                        if(!$this->requestResource($curProc->getProcNumber(), $inst[self::ARGUMENT]))
                        {
                            $curProc->setBlocked();
                            $curProc->incrementRunTime();

                            if($this->debug)
                                print("\t(resource " . $inst[self::ARGUMENT] . " unavailable)\n");
                        }
                        else
                        {
                            $curProc->advanceInstructions();
                            $curProc->incrementRunTime();

                            if($this->debug)
                                print("\t(resource " . $inst[self::ARGUMENT] . " allocated)\n");
                        
                            ++$this->time;
                        }

                        if($this->graph->isCyclic())
                        {
                            print("Deadlock detected at time " . $this->time . " involving...\n");
                            print("processes: \n");
                            foreach($this->processes as $process)
                                if($process->getState() != "TERMINATED")
                                    print(($process->getProcNumber() + 1) . " ");

                            print("\n");

                            print("resources: \n");
                            for($i = 0; $i < $this->nr; ++$i)
                                if($this->graph->getInDegree($i + $this->nr))
                                    print(($i + 1) . " ");

                            print("\n\n");

                            $this->deadlock = true;
                        }

                        break;
                    case self::RELEASE:

                        if($this->debug)
                            print("\t(resource " . $inst[self::ARGUMENT] . " released)\n");

                        $curProc->incrementRunTime();

                        $this->releaseResource($curProc->getProcNumber(), $inst[self::ARGUMENT]);
                        $curProc->advanceInstructions();
                        // Find process pointing to the resource is the highest priority, unblock it, and place it in the back of the waiting queue.
                        for($i = 0; $i < count($this->processes); ++$i)
                        {
                            if($this->graph->getEdgeWeight($this->processes[$i]->getProcNumber(), ($inst[self::ARGUMENT] + $this->np - 1)) != null &&
                               $this->graph->getEdgeWeight($this->processes[$i]->getProcNumber(), ($inst[self::ARGUMENT] + $this->np - 1)) == $this->graph->getMaxWeightIn($inst[self::ARGUMENT] + $this->np - 1))
                            {
                                // Unblocked!
                                if($this->processes[$i]->getState() == "BLOCKED")
                                {
                                    $this->processes[$i]->setWaiting();
                                    if($this->debug)
                                        print("\t(process " . ($this->processes[$i]->getProcNumber() + 1) . " unblocked)\n");
                                }

                                for($j = 0; $j < count($this->waiting); ++$j)
                                {
                                    // Cycle the queue so the unblocked process is in the back
                                    $tmp = array_shift($this->waiting);

                                    // This gets put back in the queue
                                    array_push($this->waiting, $tmp);
                                    if($tmp->getProcId() == $this->processes[$i]->getProcId())
                                        break;
                                }
                                break;
                            }
                        }

                        if($this->graph->isCyclic())
                        {
                            print("Deadlock detected at time " . $this->time . " involving...\n");
                            print("processes: \n");
                            foreach($this->processes as $process)
                                if($process->getState() != "TERMINATED")
                                    print(($process->getProcNumber() + 1) . " ");

                            print("\n");

                            print("resources: \n");
                            for($i = 0; $i < $this->nr; ++$i)
                                if($this->graph->getInDegree($i + $this->nr))
                                    print(($i + 1) . " ");

                            print("\n\n");

                            $this->deadlock = true;
                        }

                        ++$this->time;
                        break;
                    case self::COMPUTE:
                        $curProc->compute();
                        $curProc->incrementRunTime();

                        if($curProc->getComputeTime() == 0)
                            $curProc->advanceInstructions();
                        ++$this->time;
                        break;
                    default:
                        break;
                }
            }

            if($curProc->instructionsEmpty())
            {
                if($this->debug)
                    print("\t(process " . ($curProc->getProcNumber() + 1) .  " terminated)\n");
                $curProc->setTerminatedTime($this->time);
                $curProc->setTerminated();
            }
            // Else, push it back on the queue
            else
                array_push($this->waiting, $curProc);

        }

        if(!$this->deadlock)
        {
            print("All processes successfully terminated.\n");


            $i = 1;
            foreach($this->processes as $process)
                print("Process " . $i++ . ": run time = " . $process->getRunTime() . ", ended at " . ($process->getTerminatedTime() - 1) . "\n");

            print("\n");

        }

    }

    /**
     * A process requests exclusive use of a resource
     *
     * @param int process The zero-indexed process number (P1 is at 0, etc)
     * @param int resource The zero-indexed resource number (R1 is at 0, etc)
     *
     * @return boolean rval True if the resource was allocated, false otherwise
     */
    protected function requestResource($process, $resource)
    {
        $rval = false;

        $processLoc = $process;

        $resourceLoc = ($this->np - 1) + $resource;

        // If the resource was not already requested, do a request
        if(!$this->graph->connectsTo($processLoc, $resourceLoc))
        {
            // Request
            // The weight will be the priority of the requests
            // So, if there are 3 processes requesting the resource, the in-degree will be 3, and that will be the weight.
            // So this process would be 3rd in line. 
            $priority = $this->graph->getMaxWeightIn($resourceLoc);
            $edge1 = new Edge($this->graph, $processLoc, $resourceLoc, ($priority + 1));
            $this->graph->insertEdge($edge1);
        }

        // If the resource is not occupied, allocate it 
        if($this->graph->getOutDegree($resourceLoc) == 0)
        {

            // ACCESS GRANTED! Resource is now allocated to the requesting process
            $edge2 = new Edge($this->graph, $resourceLoc, $processLoc, 1);
            $this->graph->insertEdge($edge2);
            $this->graph->removeEdge($processLoc, $resourceLoc);

            $rval = true;
        }

        return $rval;
    }

    /**
     * A process releases exclusive use of a resource
     *
     * @param int process The zero-indexed process number (P1 is at 0, etc)
     * @param int resource The zero-indexed resource number (R1 is at 0, etc)
     *
     * @return boolean rval True if the resource was allocated, false otherwise
     */
    protected function releaseResource($process, $resource)
    {
        $processLoc = $process;
        $resourceLoc = ($this->np - 1) + $resource;

        // $this->graph->removeEdge($processLoc, $resourceLoc);
        $this->graph->removeEdge($resourceLoc, $processLoc);

    }

    /**
     * Sets the debug
     *
     * @param bool debug 
     */
    protected function setDebug($debug)
    {
        $this->debug = $debug;
    }

    /**
     * Get the debug
     *
     * @return bool true if debug is true
     */
    protected function getDebug()
    {
        return($this->debug);
    }

    /**
     * Main program.
     *
     * @return integer Zero on success; non-zero on failure.
     */
    public static function main()
    {
        printf("Simulation testing.\n");
        
        $status = 0;

        /* 3 3
         * 5   1 1     1 2     3 2     2 1     2 2
         * 5   1 1     1 2     3 2     2 1     2 2
         * 4   1 3     3 5     2 3     3 2
         */

        $simData = array();

        $npnr    = array();
        array_push($npnr, 3);
        array_push($npnr, 3);
        array_push($simData, $npnr);

        $line1   = array();
        array_push($line1, 5);
        array_push($line1, 1);
        array_push($line1, 1);
        array_push($line1, 1);
        array_push($line1, 2);
        array_push($line1, 3);
        array_push($line1, 2);
        array_push($line1, 2);
        array_push($line1, 1);
        array_push($line1, 2);
        array_push($line1, 2);
        array_push($simData, $line1);

        $line2   = array();
        array_push($line2, 5);
        array_push($line2, 1);
        array_push($line2, 1);
        array_push($line2, 1);
        array_push($line2, 2);
        array_push($line2, 3);
        array_push($line2, 2);
        array_push($line2, 2);
        array_push($line2, 1);
        array_push($line2, 2);
        array_push($line2, 2);
        array_push($simData, $line2);

        $line3   = array();
        array_push($line3, 4);
        array_push($line3, 1);
        array_push($line3, 3);
        array_push($line3, 3);
        array_push($line3, 5);
        array_push($line3, 2);
        array_push($line3, 3);
        array_push($line3, 3);
        array_push($line3, 2);
        array_push($simData, $line3);


        $simulation = new Simulation($simData, true);
print($simulation);
        $simulation->simulate();
        print("\n");
        // $tokenizedProgram = $Simulation->scan($filename);
    

        return $status;
    }
}

// If we are trying to execute this class directly
if(realpath($argv[0]) == realpath(__FILE__))
{
    exit(Simulation::main($argv[1]));
}
?>
